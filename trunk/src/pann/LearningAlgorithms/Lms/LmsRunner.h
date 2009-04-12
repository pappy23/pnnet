
#ifndef LMSRUNNER_H
#define LMSRUNNER_H

#include "Core/Includes.h"
#include "Core/Runner.h"
#include "Core/Neuron.h"
#include "Core/Net.h"
#include "LmsAttributes.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann
{
    class LmsFeedforwardRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        LmsFeedforwardRunner() throw();

    public:
        ~LmsFeedforwardRunner() throw();

    public:
        static Runner& Instance() throw();
        virtual void run(Neuron& _neuron, const Net& _net) throw();
        virtual RunDirection getDirection() throw();
    };

    class LmsBackpropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        LmsBackpropagationRunner() throw();

    public:
        ~LmsBackpropagationRunner() throw();

    public:
        static Runner& Instance() throw();
        virtual void run(Neuron& _neuron, const Net& _net) throw(E<Exception::NotReady>);
        virtual RunDirection getDirection() throw();
    };
}; //pann

#endif

