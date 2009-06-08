
#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include "Neuron.h"
#include "Runner.h"

namespace pann
{
    //TODO Template methods
    class NeuronFactory
    {
        NeuronFactory();

    public:
        static NeuronPtr PyramidalNeuron(
                ActivationFunctionPtr _af = ActivationFunctionPtr((ActivationFunction*)(0)),
                WeightPtr _bias = WeightPtr((Weight*)(0)),
                RunnerPtr _fireRunner = RunnerPtr((Runner*)(0)),
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

