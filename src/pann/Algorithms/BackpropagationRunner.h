#ifndef PANN_ALGORITHMS_BACKPROPAGATIONRUNNER_H_INCLUDED
#define PANN_ALGORITHMS_BACKPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Sample runner for Backpropagation through network
     */
    class BackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(BackpropagationRunner, Runner);

        virtual void run(Object const * net, NeuronPtr neuron) const;
    }; //BackpropagationRunner
    REGISTER_SINGLETON_H(BackpropagationRunner);

}; //pann

#endif //PANN_ALGORITHMS_BACKPROPAGATIONRUNNER_H_INCLUDED

