/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Includes/BoostSerialization.h"

#include "Type.h"

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
        virtual void run(NeuronPtr, Net*) const = 0;
        virtual RunDirection getDirection() const = 0;
    };

    /**
     * Runner that does nothing
     */
    class NullFeedforwardRunner : public Runner
    {
        SINGLETON_SKELETON(NullFeedforwardRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    }; //NullFeedforwardRunner
    REGISTER_SINGLETON_H(NullFeedforwardRunner);

    /**
     * Runner that does nothing
     */
    class NullBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(NullBackpropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    }; //NullBackpropagationRunner
    REGISTER_SINGLETON_H(NullBackpropagationRunner);

    /**
     * Sample runner for Feedforfard propagation through network
     */
    class FeedforwardPropagationRunner : public Runner
    {
        SINGLETON_SKELETON(FeedforwardPropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    }; //FeedforwardPropagationRunner
    REGISTER_SINGLETON_H(FeedforwardPropagationRunner);

    /**
     * Sample runner for Backpropagation through network
     */
    class BackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(BackpropagationRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    }; //BackpropagationRunner
    REGISTER_SINGLETON_H(BackpropagationRunner);

}; //pann

#endif //RUNNER_H
