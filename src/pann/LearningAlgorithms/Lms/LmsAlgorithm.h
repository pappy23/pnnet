
#ifndef LMSALGORITHM_H
#define LMSALGORITHM_H

#include "Core/Includes.h"
#include "Core/LearningAlgorithm.h"
#include "LmsRunner.h"

namespace pann
{
    class Lms : public LearningAlgorithm
    {
        /* Public interface */
    public:
        /**
         * Adds LearningHint to network object,
         * sets different parametrs, such as learning rate,
         * momentum etc.
         */
        static void init(Net& _net /* Params */);

        /**
         * Does one forward propagation and backpropagation,
         * while changing weights.
         * If _trainData.data.size() == 1, then does iterative learning,
         * else - batch learning.
         * All data is used for training and no testing performed
         */
        static void train(Net& _net, TrainData& _trainData);

    private:
        //TODO Place it in separate common module
        static Float randFloat(Float _min, Float _max) throw();
        static void randomizeWeightsGauss(Net& _net, Float _min, Float _max) throw();
    };
}; //pann

#endif //LMS_H

