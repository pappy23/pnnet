
#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include "Neuron.h"
#include "Runner.h"
#include "ActivationFunction.h"

namespace pann
{
    //TODO Template methods
    class NeuronFactory
    {
        NeuronFactory();

    public:
        static NeuronPtr PyramidalNeuron(
                ActivationFunctionPtr _af = TanH::Instance(),
                WeightPtr _bias = WeightPtr((Weight*)(0)),
                RunnerPtr _fireRunner = PyramidalNeuronFeedforwardRunner::Instance(),
                RunnerPtr _learnRunner = RunnerPtr((Runner*)(0))
            )
        {
            NeuronPtr n(new Neuron());
            n->activationFunction = _af;
            n->bias = _bias;
            n->fireRunner = _fireRunner;
            n->learnRunner = _learnRunner;

            return n;
        };

    }; //NeuronFactory

}; //pann

#endif

