
#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include "Neuron.h"

namespace pann
{
    class NeuronFactory
    {
        NeuronFactory();

    public:
        static NeuronPtr PyramidalNeuron(
                ActivationFunctionPtr _af = ActivationFunctionPtr((ActivationFunction*)(0)),
                WeightPtr _bias = WeightPtr((Weight*)(0)),
                StrategyPtr _fireStrategy = StrategyPtr((Strategy*)(0)),
                StrategyPtr _learnStrategy = StrategyPtr((Strategy*)(0))
            )
        {
            NeuronPtr n(new Neuron());
            n->activationFunction = _af;
            n->bias = _bias;
            n->fireStrategy = _fireStrategy;
            n->learnStrategy = _learnStrategy;

            return n;
        };

    }; //NeuronFactory

}; //pann

#endif

