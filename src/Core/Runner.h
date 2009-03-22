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

    class Runner //singleton
    {
    public:
        static Runner* Instance();

        virtual void run(Neuron*) = 0;
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

        virtual void run(Neuron* _neuron)
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

        virtual void run(Neuron* _neuron)
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

        void run(Neuron* _neuron)
        {
            BOOST_FOREACH( Link& link, _neuron->links )
            {
                if(link.getDirection() == Link::in)
                    _neuron->receptiveField += link.getTo()->activationValue * link.getWeight()->value;
            }

            _neuron->activationValue = _neuron->getActivationFunction()->f(_neuron->receptiveField);
            _neuron->receptiveField = 0;
        };

        virtual RunDirection getDirection()
        {
            return ForwardRun;
        };
    };

}; //pann

#endif //RUNNER_H
