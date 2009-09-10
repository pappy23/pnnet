//NeuronFactory.cpp

#include "NeuronFactory.h"
#include "Neuron.h"

namespace pann
{
    namespace NeuronFactory
    {
        NeuronPtr
        CustomNeuron(
                ActivationFunctionPtr _af,
                WeightPtr _bias,
                RunnerPtr _fireRunner,
                RunnerPtr _learnRunner
            )
        {
            NeuronPtr n(new Neuron());
            n->setActivationFunction(_af);
            n->setBias(_bias);
            n->setFireRunner(_fireRunner);
            n->setLearnRunner(_learnRunner);

            return n;
        }; //CustomNeuron
    }; //NeuronFactory
}; //pann

