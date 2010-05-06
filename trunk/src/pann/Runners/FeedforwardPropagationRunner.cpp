//FeedforwardPropagationRunner.cpp

#include "FeedforwardPropagationRunner.h"

REGISTER_SINGLETON_CPP(FeedforwardPropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    FeedforwardPropagationRunner::run(ObjectPtr net, NeuronPtr _neuron) const
    {
        neuron->fire(net, neuron);
    } //run

}; //pann
