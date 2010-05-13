#ifndef PANN_ALGORITHMS_FEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED
#define PANN_ALGORITHMS_FEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Sample runner for Feedforfard propagation through network
     */
    class FeedforwardPropagationRunner : public Runner
    {
        SINGLETON_SKELETON(FeedforwardPropagationRunner, Runner);

        virtual void run(ObjectConstPtr net, NeuronPtr neuron) const;
    }; //FeedforwardPropagationRunner
    REGISTER_SINGLETON_H(FeedforwardPropagationRunner);

}; //pann

#endif //PANN_ALGORITHMS_FEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

