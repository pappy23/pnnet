/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Type.h"
#include "Net.h"
#include "Neuron.h"

namespace pann
{
    class Net;
    class Neuron;

    enum RunDirection { ForwardRun, BackwardRun };

    /**
     * Runner interface
     */
    class Runner //singleton
    {
    public:
        static Runner& Instance();
        virtual void run(Neuron&, const Net&) = 0;
        virtual RunDirection getDirection() = 0;
    };

    /**
     * Sample runner for Feedforfard propagation through network
     */
    class FeedforwardPropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        FeedforwardPropagationRunner() {};
        
    public:    
        ~FeedforwardPropagationRunner() {};

    public:
        static Runner& Instance()
        {
            if(!self)
                self = new FeedforwardPropagationRunner();

            return *self;
        }

        virtual void run(Neuron& _neuron, const Net& _net)
        {
            _neuron.fire();
        }

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }
    };
}; //pann

#endif //RUNNER_H
