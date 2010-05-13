#ifndef PANN_ALGORITHMS_RANDOMIZEWEIGHTSGAUSS_H_INCLUDED
#define PANN_ALGORITHMS_RANDOMIZEWEIGHTSGAUSS_H_INCLUDED

#include "Core/Runner.h"
#include "Core/Net.h"

namespace pann {
    /**
     * Assign initial weights from interval [_min; _max]
     * _min = -0.3, _max = +0.3 is good choise
     */
    class RandomizeWeightsGaussRunner : public Runner
    {
        SINGLETON_SKELETON(RandomizeWeightsGaussRunner, Runner);

        virtual void run(ObjectConstPtr net, NeuronPtr neuron) const;
    };
    REGISTER_SINGLETON_H(RandomizeWeightsGaussRunner);

    void randomize_weights_gauss(NetPtr net, Float min = -0.3, Float max = +0.3);

}; //pann

#endif //PANN_ALGORITHMS_RANDOMIZEWEIGHTSGAUSSALGORITHM_H_INCLUDED

