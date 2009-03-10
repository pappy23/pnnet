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

        void run(NeuronIter _neuron)
        {
            std::cout<<_neuron->first<<" "<<std::endl;
        } 
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
                _neuron->second.receptiveField += ( link.to->second.getActivationValue() * link.getW().value );

            _neuron->second.activate();
            
            //Debug
            //std::cout<<_neuron->first<<": "<<_neuron->second.getActivationValue()<<std::endl;
        } 
    };

}; //pann

#endif //RUNNER_H
