#ifndef PANN_ALGORITHMS_TRACER_H_INCLUDED
#define PANN_ALGORITHMS_TRACER_H_INCLUDED

#include "Core/Runner.h"
#include "Core/Net.h"

namespace pann
{
    /**
     * Runner for pyramidal neurons feedforward propagation
     */
    class TracerRunner : public Runner
    {
        SINGLETON_SKELETON(TracerRunner, Runner);

        virtual void run(Object const * net, NeuronPtr neuron) const;
    }; //TracerRunner
    REGISTER_SINGLETON_H(TracerRunner);

    void trace(NetPtr net);

}; //pann

#endif //PANN_ALGORITHMS_TRACER_H_INCLUDED

