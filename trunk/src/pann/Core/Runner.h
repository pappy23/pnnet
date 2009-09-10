/*
 * @file
 * Generic runner interface
 */

#ifndef PANN_CORE_RUNNER_H_INCLUDED
#define PANN_CORE_RUNNER_H_INCLUDED

#include "Type.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Neuron);
    ADD_PTR_TYPEDEF(Net);

    enum RunDirection { ForwardRun, BackwardRun };

    /**
     * Runner interface
     */
    class Runner
    {
    public:
        virtual void run(NeuronPtr, Net*) const = 0; //FIXME: replace Net* with shared_ptr<>
        virtual RunDirection getDirection() const = 0;
    };
}; //pann

#endif //PANN_CORE_RUNNER_H_INCLUDED

