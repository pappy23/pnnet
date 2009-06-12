
#ifndef LMSRUNNER_H
#define LMSRUNNER_H

#include "Core/Exception.h"
#include "Core/Runner.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann
{
    class LmsBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(LmsBackpropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    };
    REGISTER_SINGLETON_H(LmsBackpropagationRunner);
}; //pann

#endif

