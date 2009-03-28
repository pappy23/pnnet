/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Includes.h"
#include "Type.h"
#include "Neuron.h"

namespace pann
{
    class Net;

    enum RunDirection { ForwardRun, BackwardRun };

    class Runner //singleton
    {
    public:
        static Runner* Instance();
        virtual void run(Neuron*, const Net*) = 0;
        virtual RunDirection getDirection() = 0;
    };

    class NullRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        NullRunner();

    public:
        ~NullRunner();

    public:
        static Runner* Instance();
        virtual void run(Neuron* _neuron, const Net* _net);
        virtual RunDirection getDirection();
    };

    class NullBackpropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        NullBackpropagationRunner();

    public:
        ~NullBackpropagationRunner();

    public:
        static Runner* Instance();
        virtual void run(Neuron* _neuron, const Net* _net);
        virtual RunDirection getDirection();
    };

    class FeedforwardPropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        FeedforwardPropagationRunner();
        
    public:    
        ~FeedforwardPropagationRunner();

    public:
        static Runner* Instance();
        virtual void run(Neuron* _neuron, const Net* _net);
        virtual RunDirection getDirection();
    };

}; //pann

#endif //RUNNER_H
