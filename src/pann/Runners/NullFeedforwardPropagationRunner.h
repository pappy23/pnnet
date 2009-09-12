#ifndef PANN_RUNNERS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED
#define PANN_RUNNERS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Runner that does nothing
     */
    class NullFeedforwardPropagationRunner : public Runner
    {
        SINGLETON_SKELETON(NullFeedforwardPropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    }; //NullFeedforwardPropagationRunner
    REGISTER_SINGLETON_H(NullFeedforwardPropagationRunner);

}; //pann

#endif //PANN_RUNNERS_NULLFEEDFORWARDPROPAGATIONRUNNER_H_INCLUDED

