//BackpropagationRunner.cpp

#include "BackpropagationRunner.h"

REGISTER_SINGLETON_CPP(BackpropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    BackpropagationRunner::run(Object const * net, NeuronPtr neuron) const
    {
        neuron->learn->run(net, neuron);
    } //run

}; //pann

