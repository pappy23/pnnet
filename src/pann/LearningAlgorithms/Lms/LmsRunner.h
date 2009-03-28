
#ifndef LMSRUNNER_H
#define LMSRUNNER_H

#include "Core/Includes.h"
#include "Core/Runner.h"
#include "Core/Neuron.h"
#include "LmsAttributes.h"

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
        static Runner* Instance() throw();
        virtual void run(Neuron* _neuron) throw();
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
        static Runner* Instance() throw();
        virtual void run(Neuron* _neuron) throw(E<Exception::NotReady>);
        virtual RunDirection getDirection() throw();
    };
}; //pann

#endif

