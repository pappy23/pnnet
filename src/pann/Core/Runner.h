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
    class Runner
    {
    public:
        virtual void run(Neuron&, const Net&) = 0;
        virtual RunDirection getDirection() = 0;
    };

    /**
     * Sample runner for Feedforfard propagation through network
     */
    class FeedforwardPropagationRunner : public Runner
    {
        //Singleton
        FeedforwardPropagationRunner() {};
        ~FeedforwardPropagationRunner() {};

    public:
        static Runner& Instance()
        {
            static FeedforwardPropagationRunner self;
            return self;
        }

        virtual void run(Neuron& _neuron, const Net& _net)
        {
            _neuron.fire();
        }

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }
    }; //FeedforwardPropagationRunner

    class BackPropagationRunner : public Runner
    {
        //Singleton
        BackPropagationRunner() {};
        ~BackPropagationRunner() {};

    public:
        static Runner& Instance()
        {
            static BackPropagationRunner self;
            return self;
        }

        virtual void run(Neuron& _neuron, const Net& _net)
        {
            _neuron.learn();
        }

        virtual RunDirection getDirection()
        {
            return BackwardRun;
        }
    }; //BackPropagationRunner

}; //pann

#endif //RUNNER_H
