#ifndef PANN_RUNNERS_RANDOMIZEWEIGHTSGAUSSRUNNER_H_INCLUDED
#define PANN_RUNNERS_RANDOMIZEWEIGHTSGAUSSRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann {
    /**
     * Assign initial weights from interval [_min; _max]
     * _min = -0.3, _max = +0.3 is good choise
     */
    class RandomizeWeightsGaussRunner : public Runner
    {
        SINGLETON_SKELETON(RandomizeWeightsGaussRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;
    };
    REGISTER_SINGLETON_H(RandomizeWeightsGaussRunner);
}; //pann

#endif //PANN_RUNNERS_RANDOMIZEWEIGHTSGAUSSRUNNER_H_INCLUDED

