
#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include "Type.h"

namespace pann
{
    namespace NeuronFactory
    {
        NeuronPtr CustomNeuron(
                ActivationFunctionPtr _af,
                WeightPtr _bias,
                RunnerPtr _fireRunner,
                RunnerPtr _learnRunner
            );
    }; //NeuronFactory

}; //pann

#endif

