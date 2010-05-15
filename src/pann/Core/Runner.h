/*
 * @file
 * Generic runner interface
 */

#ifndef PANN_CORE_RUNNER_H_INCLUDED
#define PANN_CORE_RUNNER_H_INCLUDED

#include "Includes/BoostSerialization.h"
#include "Type.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Object);
    ADD_PTR_TYPEDEF(Neuron);

    /**
     * Runner interface
     */
    class Runner
    {
    public:
        virtual void run(Object const *, NeuronPtr) const = 0;
    }; //Runner
    ADD_PTR_TYPEDEF(Runner);

}; //pann

#endif //PANN_CORE_RUNNER_H_INCLUDED

