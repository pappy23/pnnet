/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Type.h"

namespace pann
{
    class Net;
    class Neuron;

    enum RunDirection { ForwardRun, BackwardRun };

    class Runner //singleton
    {
    public:
        static Runner& Instance();
        virtual void run(Neuron&, const Net&) = 0;
        virtual RunDirection getDirection() = 0;
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
        static Runner& Instance();
        virtual void run(Neuron& _neuron, const Net& _net);
        virtual RunDirection getDirection();
    };

}; //pann

#endif //RUNNER_H
