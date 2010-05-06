//BackpropagationRunner.cpp

#include "BackpropagationRunner.h"

REGISTER_SINGLETON_CPP(BackpropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    BackpropagationRunner::run(ObjectPtr net, NeuronPtr neuron) const
    {
        neuron->learn(net, neuron);
    } //run

}; //pann

