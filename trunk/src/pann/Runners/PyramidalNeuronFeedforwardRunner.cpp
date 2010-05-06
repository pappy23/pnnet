//PyramidalNeuronFeedforwardRunner.cpp

#include "PyramidalNeuronFeedforwardRunner.h"

REGISTER_SINGLETON_CPP(PyramidalNeuronFeedforwardRunner);

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Tf.h"

namespace pann {
    void
    PyramidalNeuronFeedforwardRunner::run(ObjectPtr net, NeuronPtr neuron) const
    {
        if(neuron->tf)
        {
            if(neuron->bias)
                neuron->input += neuron->bias->value;

            BOOST_FOREACH( const Link& link, neuron->input_connections )
                neuron->input += link.get_to()->output * link.get_weight()->value;

            neuron->output = neuron->tf->fx(neuron->input);
        }

        neuron->input = 0;
    } //run

}; //pann

