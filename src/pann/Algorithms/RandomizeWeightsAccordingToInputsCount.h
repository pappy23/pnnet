#ifndef PANN_ALGORITHMS_RANDOMIZEWEIGHTSACCORDINGTOINPUTSCOUNT_H_INCLUDED
#define PANN_ALGORITHMS_RANDOMIZEWEIGHTSACCORDINGTOINPUTSCOUNT_H_INCLUDED

#include "Core/Runner.h"
#include "Core/Net.h"

namespace pann {
    /**
     * Weight is random number from [_min/sqrt(C); _max/sqrt(C)]
     * C - number of inputs in current neuron
     * _min = -2.4, _max = +2.4 is good choise
     * See Gradien-Based Learning Applied to Document Recognition, Yann LeCun, app1, p.41
     * See S. Haykin, p252
     */
    class RandomizeWeightsAccordingToInputsCountRunner : public Runner
    {
        SINGLETON_SKELETON(RandomizeWeightsAccordingToInputsCountRunner, Runner);

        virtual void run(ObjectConstPtr net, NeuronPtr neuron) const;
    }; //RandomizeWeightsAccordingToInputsCountRunner
    REGISTER_SINGLETON_H(RandomizeWeightsAccordingToInputsCountRunner);

    void randomize_weights_according_to_inputs_count(NetPtr net, Float min = -2.4, Float max = +2.4);

}; //pann

#endif //PANN_ALGORITHMS_RANDOMIZEWEIGHTSACCORDINGTOINPUTSCOUNTRUNNER_H_INCLUDED

