/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Type.h"
#include "Net.h"
#include "Neuron.h"
#include "ActivationFunction.h"

using boost::shared_ptr;

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

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            const RunnerPtr& r = _neuron->getFireRunner();

            if(r && r->getDirection() == ForwardRun)
            {
                r->run(_neuron, _net);
            } else {
                throw Exception()<<"Wrong runner\n";
            }
        }

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

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            const RunnerPtr& r = _neuron->getFireRunner();

            if(r && r->getDirection() == BackwardRun)
            {
                r->run(_neuron, _net);
            } else {
                throw Exception()<<"Wrong runner\n";
            }
        }

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }
    }; //BackpropagationRunner
    REGISTER_SINGLETON_H(BackpropagationRunner);

    /**
     * Runner for pyramidal neurons feedforward propagation
     */
    class PyramidalNeuronFeedforwardRunner : public Runner
    {
        SINGLETON_SKELETON(PyramidalNeuronFeedforwardRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            if(_neuron->getActivationFunction())
            {
                if(_neuron->getBias())
                    _neuron->receptiveField += _neuron->getBias()->getValue();

                BOOST_FOREACH( const Link& link, _neuron->getInConnections() )
                    _neuron->receptiveField += link.getTo()->getOutput() * link.getWeight()->getValue();

                _neuron->activationValue = _neuron->getActivationFunction()->f(_neuron->receptiveField);
            }

            _neuron->receptiveField = 0;
        }

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    }; //PyramidalNeuronFeedforwardRunner
    REGISTER_SINGLETON_H(PyramidalNeuronFeedforwardRunner);

}; //pann

#endif //RUNNER_H
