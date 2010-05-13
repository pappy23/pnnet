//FeedforwardPropagationRunner.cpp

#include "FeedforwardPropagationRunner.h"

REGISTER_SINGLETON_CPP(FeedforwardPropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    FeedforwardPropagationRunner::run(ObjectConstPtr net, NeuronPtr neuron) const
    {
        neuron->fire->run(net, neuron);
    } //run

}; //pann
