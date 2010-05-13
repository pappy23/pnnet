#ifndef PANN_ALGORITHMS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED
#define PANN_ALGORITHMS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Runner that does nothing
     */
    class NullBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(NullBackpropagationRunner, Runner);

        virtual void run(ObjectConstPtr net, NeuronPtr neuron) const
        {
            //Nothing
        }
    }; //NullBackpropagationRunner
    REGISTER_SINGLETON_H(NullBackpropagationRunner);
}; //pann

#endif //PANN_ALGORITHMS_NULLBACKPROPAGATIONRUNNER_H_INCLUDED

