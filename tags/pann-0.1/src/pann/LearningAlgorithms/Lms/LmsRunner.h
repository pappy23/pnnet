
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
    private:
        static Runner* self;

    private:
        LmsBackpropagationRunner();

    public:
        ~LmsBackpropagationRunner();

    public:
        static Runner& Instance();
        virtual void run(Neuron& _neuron, const Net& _net);
        virtual RunDirection getDirection();
    };
}; //pann

#endif

