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
    enum RunDirection { ForwardRun, BackwardRun };

    class Runner
    {
    public:
        static Runner* Instance();

        virtual void run(NeuronIter) = 0;
        virtual RunDirection getDirection() = 0;
    };

    class NullRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        NullRunner() { };

    public:
        ~NullRunner() { };

    public:
        static Runner* Instance()
        {
            if(!self)
                self = new NullRunner();

            return self;
        };

        virtual void run(NeuronIter _neuron)
        {
        };

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        };
    };

    class NullBackpropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        NullBackpropagationRunner() { };

    public:
        ~NullBackpropagationRunner() { };

    public:
        static Runner* Instance()
        {
            if(!self)
                self = new NullBackpropagationRunner();

            return self;
        };

        virtual void run(NeuronIter _neuron)
        {
        };

        virtual RunDirection getDirection()
        {
            return BackwardRun;
        };
    };

    class FeedforwardPropagationRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        FeedforwardPropagationRunner() { };
        
    public:    
        ~FeedforwardPropagationRunner() { };

    public:
        static Runner* Instance()
        {
            if(!self)
                self = new FeedforwardPropagationRunner();

            return self;
        };

        void run(NeuronIter _neuron)
        {
            BOOST_FOREACH( Link& link, _neuron->second.links )
            {
                if(link.getDirection() == Link::in)
                {
                    _neuron->second.receptiveField += 
                        ( link.getToIter()->second.activationValue * link.getWeightIter()->second.value );
                }
            }

            _neuron->second.activationValue = _neuron->second.getActivationFunction()->f(_neuron->second.receptiveField);
            _neuron->second.receptiveField = 0;
        };

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        };
    };

}; //pann

#endif //RUNNER_H
