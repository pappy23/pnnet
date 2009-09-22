//PyramidalNeuronFactory.h

#ifndef PYRAMIDALNEURONFACTORY_H
#define PYRAMIDALNEURONFACTORY_H

#include "Core/NeuronFactory.h"
#include "PyramidalNeuronFeedforwardRunner.h"

namespace pann
{
    namespace NeuronFactory
    {
        template<class ActivationFunctionType, class LearningRunnerType>
        static NeuronPtr PyramidalNeuron(WeightPtr _bias = WeightPtr((Weight*)0))
        {
            return CustomNeuron(
                    ActivationFunctionType::Instance(),
                    _bias,
                    PyramidalNeuronFeedforwardRunner::Instance(),
                    LearningRunnerType::Instance()
                    );
        };

        static NeuronPtr PyramidalNeuron(
                ActivationFunctionPtr _af = TanH::Instance(),
                WeightPtr _bias = WeightPtr((Weight*)0),
                RunnerPtr _learnRunner = NullBackpropagationRunner::Instance()
                )
        {
            return CustomNeuron(
                    _af,
                    _bias,
                    PyramidalNeuronFeedforwardRunner::Instance(),
                    _learnRunner
                    );
        };

    }; // NeuronFactory
}; //pann

#endif

