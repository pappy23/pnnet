#ifndef PANN_ALGORITHMS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED
#define PANN_ALGORITHMS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Runner that does nothing
     */
    class NullFeedforwardPropagationRunner : public Runner
    {
        SINGLETON_SKELETON(NullFeedforwardPropagationRunner, Runner);

        virtual void run(Object const * net, NeuronPtr neuron) const
        {
            //Nothing
        }
    }; //NullFeedforwardPropagationRunner
    REGISTER_SINGLETON_H(NullFeedforwardPropagationRunner);

}; //pann

#endif //PANN_ALGORITHMS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

