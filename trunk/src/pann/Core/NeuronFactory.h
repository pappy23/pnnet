
#ifndef NEURONFACTORY_H
#define NEURONFACTORY_H

#include "Neuron.h"
#include "Runner.h"
#include "ActivationFunction.h"

namespace pann
{
    class NeuronFactory
    {
        NeuronFactory();

    public:
        static NeuronPtr CustomNeuron(
                ActivationFunctionPtr _af,
                WeightPtr _bias,
                RunnerPtr _fireRunner,
                RunnerPtr _learnRunner
            )
        {
            NeuronPtr n(new Neuron());
            n->activationFunction = _af;
            n->bias = _bias;
            n->fireRunner = _fireRunner;
            n->learnRunner = _learnRunner;

            //TODO Fix me
            if(_bias)
            {
                _bias->incUsageCount();
                _bias->incUsageCount();
            }

            return n;
        };

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

    }; //NeuronFactory

}; //pann

#endif

