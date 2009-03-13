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
    protected:
        static Runner* self;
        static int refcount;
        Runner() { };
        virtual ~Runner() { };

    public:
        static Runner& Instance();
        void freeInstance()
        {
            refcount--;
            if(!refcount)
            {
                delete this;
                self = 0;
            }
        };

        virtual void run(NeuronIter) = 0;
        virtual RunDirection direction() = 0;
    };

    class NullRunner : public Runner
    {
    protected:
        NullRunner() { };
        ~NullRunner() { };

    public:
        static Runner& Instance()
        {
            if(!self)
                self = new NullRunner();

            refcount++;

            return *self;
        };

        virtual void run(NeuronIter _neuron)
        {
            std::cout<<_neuron->first<<" "<<std::endl;
        };

        virtual RunDirection direction()
        {
            return ForwardRun;
        };
    };

    class FeedforwardPropagationRunner : public Runner
    {
    protected:
        FeedforwardPropagationRunner() { };
        ~FeedforwardPropagationRunner() { };

    public:
        static Runner& Instance()
        {
            if(!self)
                self = new FeedforwardPropagationRunner();

            refcount++;

            return *self;
        };

        void run(NeuronIter _neuron)
        {
            BOOST_FOREACH( Link& link, _neuron->second.links )
                _neuron->second.receptiveField += 
                    ( link.getTo()->second.activationValue * link.getWeight()->second.value );

            _neuron->second.activationValue = _neuron->second.getActivationFunction()->f(_neuron->second.receptiveField);
            _neuron->second.receptiveField = 0;

            //Debug
            //std::cout<<_neuron->first<<": "<<_neuron->second.getActivationValue()<<std::endl;
        };

        virtual RunDirection direction()
        {
            return ForwardRun;
        };
    };

}; //pann

#endif //RUNNER_H
