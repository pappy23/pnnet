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
        //Singleton
        NullFeedforwardRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new NullFeedforwardRunner());
            return self;
        }

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<NullFeedforwardRunner, Runner>(
                    static_cast<NullFeedforwardRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //NullFeedforwardRunner

    /**
     * Runner that does nothing
     */
    class NullBackpropagationRunner : public Runner
    {
        //Singleton
        NullBackpropagationRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new NullBackpropagationRunner());
            return self;
        }

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            //Nothing
        }

        virtual RunDirection getDirection() const
        {
            return BackwardRun;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<NullBackpropagationRunner, Runner>(
                    static_cast<NullBackpropagationRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //NullBackpropagationRunner

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

        virtual void run(NeuronPtr _neuron, Net* _net) const
        {
            const RunnerPtr& r = _neuron->getFireRunner();

            if(r && r->getDirection() == ForwardRun)
            {
                r->run(_neuron, _net);
                Debug()<<_neuron->getOutput()<<"\n";
            } else {
                throw Exception()<<"Wrong runner\n";
            }
        }

        virtual RunDirection getDirection() const
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

    /**
     * Sample runner for Backpropagation through network
     */
    class BackpropagationRunner : public Runner
    {
        //Singleton
        BackpropagationRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new BackpropagationRunner());
            return self;
        }

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
            return ForwardRun;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<BackpropagationRunner, Runner>(
                    static_cast<BackpropagationRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //BackpropagationRunner

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

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<PyramidalNeuronFeedforwardRunner, Runner>(
                    static_cast<PyramidalNeuronFeedforwardRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    }; //PyramidalNeuronFeedforwardRunner

}; //pann

#endif //RUNNER_H
