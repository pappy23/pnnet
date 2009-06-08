//LmsRunner.cpp

#include "Includes/BoostCommon.h"

#include "LmsRunner.h"
#include "LmsAttributes.h"

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Weight.h"
#include "Core/ActivationFunction.h"

namespace pann
{
    void
    LmsBackpropagationRunner::run(NeuronPtr _neuron, NetPtr _net)
    {
        LmsNeuronAttributes& neuron_attrs = _neuron->get<LmsNeuronAttributes>();
        if(!neuron_attrs.parent)
            neuron_attrs.parent.reset((LmsNetAttributes*)(_net->getPtr(LmsNetAttributes::getHash()).get()));

        LmsNetAttributes& net_attrs = *neuron_attrs.parent;

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        if(neuron_attrs.error) //output neuron
            neuron_attrs.localGradient = neuron_attrs.error;
        else
            neuron_attrs.localGradient = 0;

        BOOST_FOREACH( const Link& link, _neuron->getOutConnections() )
            neuron_attrs.localGradient += link.getTo()->get<LmsNeuronAttributes>().localGradient * link.getWeight()->getValue();
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = Linear) 
        //has activation function y = x, so dy/dx = 1
        neuron_attrs.localGradient *= _neuron->getActivationFunction()->derivative_dy(_neuron->getOutput());
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
        
        //Update weights
        //Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
        //When epoch -> inf, rate -> basic_rate / epoch
        Float lr = net_attrs.learningRate / (1 + (net_attrs.epoch / net_attrs.annealingTSC));
        
        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( Link& link, _neuron->getOutConnections() )
        {
            WeightPtr w = link.getWeight();

            //See Haykin, p241
            //Ni -> Nj
            //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
            Float dw = lr * link.getTo()->get<LmsNeuronAttributes>().localGradient * _neuron->getOutput();
            
            //Momentum
            LmsLinkAttributes& link_attrs = link.get<LmsLinkAttributes>();
            dw += net_attrs.learningMomentum * link_attrs.lastDeltaW;
            link_attrs.lastDeltaW = dw;

            //Apply dw
            boost::mutex::scoped_lock lock(w->getMutex());
            w->addValue(dw);
        }

        //Update bias weight
        if(_neuron->getBias())
        {
            WeightPtr w = _neuron->getBias();

            Float dw = lr * neuron_attrs.localGradient;

            //Momentum
            //Currently there is no way to use simulated annealing with bias,
            //because it depends on lastDeltaW attribute and Weight object
            //currently doesn't hold attributes at all

            //Apply dw
            boost::mutex::scoped_lock lock(w->getMutex());
            w->addValue(dw);
        }
    } //run

}; //pann

