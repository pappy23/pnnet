#ifndef PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED
#define PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED

#include "Core/Neuron.h"
#include "Algorithms/PyramidalNeuronFeedforwardRunner.h"
#include "Algorithms/NullBackpropagationRunner.h"
#include "TF/TanH.h"

namespace pann {
namespace NeuronFactory {
    //Still not used
    /*
    template<class TfType, class LearnRunnerType>
    static NeuronPtr PyramidalNeuron(WeightPtr bias = WeightPtr((Weight*)0))
    {
        return CustomNeuron(
                TfType::Instance(),
                bias,
                PyramidalNeuronFeedforwardRunner::Instance(),
                LearnRunnerType::Instance()
                );
    };
    */

    static NeuronPtr PyramidalNeuron(
            TfPtr tf = TanH::Instance(),
            WeightPtr bias = WeightPtr((Weight*)0),
            RunnerPtr learn_runner = NullBackpropagationRunner::Instance()
            )
    {
        return NeuronPtr(new Neuron(
                tf,
                bias,
                PyramidalNeuronFeedforwardRunner::Instance(),
                learn_runner
                ));
    };
}; //NeuronFactory
}; //pann

#endif //PANN_NEURONFACTORIES_PYRAMIDALNEURON_H_INCLUDED

