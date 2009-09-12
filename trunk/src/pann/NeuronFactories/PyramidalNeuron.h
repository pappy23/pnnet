#ifndef PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED
#define PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED

#include "Core/Neuron.h"
#include "Runners/PyramidalNeuronFeedforwardRunner.h"

namespace pann {
namespace NeuronFactory {
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
        return Neuron(
                _af,
                _bias,
                PyramidalNeuronFeedforwardRunner::Instance(),
                _learnRunner
                );
    };
}; //NeuronFactory
}; //pann

#endif //PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED

