//PyramidalNeuronFeedforwardRunner.cpp

#include <boost/foreach.hpp>

#include "PyramidalNeuronFeedforwardRunner.h"

REGISTER_SINGLETON_CPP(PyramidalNeuronFeedforwardRunner);

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Tf.h"

namespace pann {
    void
    PyramidalNeuronFeedforwardRunner::run(Object const * net, NeuronPtr neuron) const
    {
        if(neuron->tf)
        {
            if(neuron->bias)
                neuron->input += neuron->bias->get_value();

            BOOST_FOREACH( const Link& link, neuron->input_links )
                neuron->input += link.get_to()->output * link.get_weight()->get_value();

            neuron->output = neuron->tf->fx(neuron->input);
        }

        neuron->input = 0;
    } //run

}; //pann

