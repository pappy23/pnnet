
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
        LmsFeedforwardRunner();

    public:
        ~LmsFeedforwardRunner();

    public:
        static Runner* Instance();
        virtual void run(Neuron* _neuron);
        virtual RunDirection getDirection();
    };

    class LmsBackpropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        LmsBackpropagationRunner();

    public:
        ~LmsBackpropagationRunner();

    public:
        static Runner* Instance();
        virtual void run(Neuron* _neuron);
        virtual RunDirection getDirection();
    };
}; //pann

#endif

