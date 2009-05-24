//LmsRunner.cpp

#include "Includes/BoostCommon.h"

#include "LmsRunner.h"
#include "LmsAttributes.h"

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Weight.h"

using namespace pann::LmsAttributes;

namespace pann
{
    Runner* LmsBackpropagationRunner::self = 0;

    LmsBackpropagationRunner::LmsBackpropagationRunner()
    {
    } //LmsBackpropagationRunner

    LmsBackpropagationRunner::~LmsBackpropagationRunner()
    {
    } //~LmsBackpropagationRunner
    
    Runner&
    LmsBackpropagationRunner::Instance()
    {
        if(!self)
            self = new LmsBackpropagationRunner();

        return *self;
    } //Instance

    void
    LmsBackpropagationRunner::run(Neuron& _neuron, const Net& _net)
    {
        if(!_neuron.is(LMS))
        {
            _neuron.erase(AlgorithmSpecificLearningParameters);
            _neuron[LMS] = 1.0;
        }

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        if(_neuron.is(error)) //output neuron
            _neuron[localGradient] = _neuron[error];
        else
            _neuron[localGradient] = 0;

        BOOST_FOREACH( const Link& link, _neuron.getOutConnections() )
            _neuron[localGradient] += link.getTo()->at(localGradient) * link.getWeight()->getValue();
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = Linear) 
        //has activation function y = x, so dy/dx = 1
        _neuron[localGradient] *= _neuron.getActivationFunction().derivative_dy(_neuron.getActivationValue());
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)
        
        //Update weights
        //Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
        //When epoch -> inf, rate -> basic_rate / epoch
        Float lr = _net[learningRate] / (1 + (_net[epoch] / _net[annealingTSC]));
        
        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( const Link& link, _neuron.getOutConnections() )
        {
            Weight& w = *link.getWeight();
            boost::mutex::scoped_lock lock(w.getMutex());

            if(!w.is(LMS))
            {
                w.erase(AlgorithmSpecificLearningParameters);
                w[LMS] = 1.0;
            }

            //See Haykin, p241
            //Ni -> Nj
            //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
            Float dw = lr * link.getTo()->at(localGradient) * _neuron.getActivationValue();
            
            if(w.getUsageCount() == 2)
            {
                //Currently there is no way to make lastDeltaW thread safe
                dw += _net[learningMomentum] * w[lastDeltaW];
                w[lastDeltaW] = dw;
            }

            w.addValue(dw);
        }

        //Update bias weight
        if(_neuron.hasBias())
        {
            Weight& w = *_neuron.getBias();
            boost::mutex::scoped_lock lock(w.getMutex());

            if(!w.is(LMS))
            {
                w.erase(AlgorithmSpecificLearningParameters);
                w[LMS] = 1.0;
            }

            Float dw = lr * _neuron[localGradient];

            if(w.getUsageCount() == 2)
            {
                //Currently there is no way to make lastDeltaW thread safe
                dw += _net[learningMomentum] * w[lastDeltaW];
                w[lastDeltaW] = dw;
            }

            w.addValue(dw);
        }
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection()
    {
        return BackwardRun;
    } //getDirection

}; //pann

