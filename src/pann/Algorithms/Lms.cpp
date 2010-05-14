//LmsRunner.cpp

#include <boost/foreach.hpp>

#include "Lms.h"

REGISTER_SINGLETON_CPP(LmsBackpropagationRunner);

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Weight.h"
#include "Core/Tf.h"

namespace pann {

    void
    LmsBackpropagationRunner::run(ObjectConstPtr net, NeuronPtr neuron) const
    {
        //Attribute table
        const Hash ERROR = hash("lms_error");
        const Hash LGRAD = hash("lms_local_gradient");
        const Hash EPOCH = hash("lms_epoch");
        const Hash ANNTSC = hash("lms_annealing_tsc");
        const Hash LEARNRATE = hash("lms_learning_rate");
        const Hash LEARNMOMENTUM = hash("lms_learning_momentum");
        const Hash LASTDW = hash("last_dw"); //Link attribute

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        Float error = neuron->get_attr(ERROR);
        if(error) //output neuron
            neuron->set_attr(LGRAD, error);
        else
            neuron->set_attr(hash("lms_local_gradient"), 0);

        BOOST_FOREACH( const Link& link, neuron->output_links )
            neuron->get_attr_ref(LGRAD) += link.get_to()->get_attr(LGRAD) * link.get_weight()->get_value();
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = Linear)
        //has activation function y = x, so dy/dx = 1
        neuron->get_attr_ref(LGRAD) *= neuron->tf->df_dy(neuron->output);
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)

        //Update weights
        //Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
        //When epoch -> inf, rate -> basic_rate / epoch
        Float lr = net->get_attr(LEARNRATE) / (1 + (net->get_attr(EPOCH) / net->get_attr(ANNTSC)));

        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( Link& link, neuron->output_links )
        {
            //See Haykin, p241
            //Ni -> Nj
            //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
            Float dw = lr * link.get_to()->get_attr(LGRAD) * neuron->output;

            //Momentum
            dw += net->get_attr(LEARNMOMENTUM) * link.get_attr(LASTDW);
            link.set_attr(LASTDW, dw);

            //Apply dw
            //boost::mutex::scoped_lock lock(w->getMutex());
            link.get_weight()->add_value(dw);
        }

        //Update bias weight
        if(neuron->bias)
        {
            Float dw = lr * neuron->get_attr(LGRAD);

            //Momentum
            //Currently there is no way to use simulated annealing with bias,
            //because it depends on lastDeltaW attribute and Weight object
            //currently doesn't hold attributes at all

            //Apply dw
            //boost::mutex::scoped_lock lock(bias->getMutex());
            neuron->bias->add_value(dw);
        }
    } //run

}; //pann

