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
        virtual void run(NeuronPtr, Net*) = 0;
        virtual RunDirection getDirection() = 0;
    };

    //TODO Backpropagation runner

    /**
     * Runner for pyramidal neurons feedforward propagation
     */
    class PyramidalNeuronFeedforwardRunner : public Runner
    {
        //Singleton
        PyramidalNeuronFeedforwardRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new PyramidalNeuronFeedforwardRunner());
            return self;
        }

        virtual void run(NeuronPtr _neuron, Net* _net)
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

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<PyramidalNeuronFeedforwardRunner, Runner>(
                    static_cast<PyramidalNeuronFeedforwardRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //FeedforwardPropagationRunner

    /**
     * Sample runner for Feedforfard propagation through network
     */
    class FeedforwardPropagationRunner : public Runner
    {
        //Singleton
        FeedforwardPropagationRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new FeedforwardPropagationRunner());
            return self;
        }

        virtual void run(NeuronPtr _neuron, Net* _net)
        {
            if(_neuron->getFireRunner())
                _neuron->getFireRunner()->run(_neuron, _net);
        }

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<FeedforwardPropagationRunner, Runner>(
                    static_cast<FeedforwardPropagationRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //FeedforwardPropagationRunner

}; //pann

#endif //RUNNER_H
