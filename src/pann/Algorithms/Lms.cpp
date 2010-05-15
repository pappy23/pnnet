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
    LmsBackpropagationRunner::run(Object const * net, NeuronPtr neuron) const
    {
        using namespace attr;

        //local_gradient = desired_output - actual_output = error - for output neuron
        //local_gradient = weighted sum of upstream neurons local_gradients
        if(neuron->is_attr(lms::error)) //output neuron
            neuron->set_attr(lms::local_gradient, neuron->get_attr(lms::error));
        else
            neuron->set_attr(lms::local_gradient, 0);

        BOOST_FOREACH( const Link& link, neuron->output_links )
            neuron->get_attr_ref(lms::local_gradient) += link.get_to()->get_attr(lms::local_gradient) * link.get_weight()->get_value();
        //Now neuron_hint[localGradient] contains error (known error for outer layer and weighted sum of
        //local gradients of all upstream neurons for other layers)

        //Save actual local gradient value
        //Note: we assume that input neuron(it's activation function = Linear)
        //has activation function y = x, so dy/dx = 1
        neuron->get_attr_ref(lms::local_gradient) *= neuron->tf->df_dy(neuron->output);
        //grad = error * df(receptiveField)/dx, but df/dx usually less preferable then df/dy,
        //grad = error * df(activationValue)/dy (see Simon Haykin, 2nd edition, p235)

        //Update weights
        //Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
        //When epoch -> inf, rate -> basic_rate / epoch
        Float lr = net->get_attr(lms::learning_rate) / (1 + (net->get_attr(lms::epoch) / net->get_attr(lms::annealing_tsc)));

        //Comment: Na --w--> Nb
        //w is updated while processing Na
        BOOST_FOREACH( Link& link, neuron->output_links )
        {
            //See Haykin, p241
            //Ni -> Nj
            //dWj(n) = a*(Wj(n-1)) + learning_rate * local_gradient_j * Yi
            Float dw = lr * link.get_to()->get_attr(lms::local_gradient) * neuron->output;

            //Momentum
            if(!link.is_attr(lms::last_dw))
                link.set_attr(lms::last_dw, 0.0);
            dw += net->get_attr(lms::learning_momentum) * link.get_attr(lms::last_dw);
            link.set_attr(lms::last_dw, dw);

            //Apply dw
            //boost::mutex::scoped_lock lock(w->getMutex());
            link.get_weight()->add_value(dw);
        }

        //Update bias weight
        if(neuron->bias)
        {
            Float dw = lr * neuron->get_attr(lms::local_gradient);

            //Momentum
            //Currently there is no way to use simulated annealing with bias,
            //because it depends on lastDeltaW attribute and Weight object
            //currently doesn't hold attributes at all

            //Apply dw
            //boost::mutex::scoped_lock lock(bias->getMutex());
            neuron->bias->add_value(dw);
        }
    }; //run

    void
    lms_init(NetPtr net)
    {
        using namespace attr::lms;

        net->set_attr(epoch, 1);
        net->set_attr(learning_rate, 0.3);
        net->set_attr(learning_momentum, 0.5);
        net->set_attr(annealing_tsc, 10);
    }; //lms_init

}; //pann

