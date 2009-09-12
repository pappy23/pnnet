#ifndef PANN_RUNNERS_BACKPROPAGATIONRUNNER_H_INCLUDED
#define PANN_RUNNERS_BACKPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Sample runner for Backpropagation through network
     */
    class BackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(BackpropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    }; //BackpropagationRunner
    REGISTER_SINGLETON_H(BackpropagationRunner);

}; //pann

#endif //PANN_RUNNERS_BACKPROPAGATIONRUNNER_H_INCLUDED

