#ifndef PANN_RUNNERS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED
#define PANN_RUNNERS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Runner that does nothing
     */
    class NullBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(NullBackpropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    }; //NullBackpropagationRunner
    REGISTER_SINGLETON_H(NullBackpropagationRunner);
}; //pann

#endif //PANN_RUNNERS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED

