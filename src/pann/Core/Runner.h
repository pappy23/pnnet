/*
 * @file
 * Generic runner interface
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "Type.h"
#include "Net.h"
#include "Neuron.h"

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
        virtual void run(NeuronPtr, NetPtr) = 0;
        virtual RunDirection getDirection() = 0;
    };

    //TODO Backpropagation runner

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

        virtual void run(NeuronPtr _neuron, NetPtr _net)
        {
            //TODO
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
