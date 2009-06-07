
#ifndef LMSALGORITHM_H
#define LMSALGORITHM_H

#include "LearningAlgorithms/LearningAlgorithm.h"

namespace pann
{
    class Net;
    class TrainData;

    class Lms : public LearningAlgorithm
    {
        /* Public interface */
    public:
        /**
         * Adds LearningHint to network object,
         * sets different parametrs, such as learning rate,
         * momentum etc.
         */
        static void init(Net& _net);

        /**
         * Does one forward propagation and backpropagation,
         * while changing weights.
         * If _trainData.data.size() == 1, then does iterative learning,
         * else - batch learning.
         * All data is used for training and no testing performed
         */
        static void train(Net& _net, TrainData& _trainData);
    };
}; //pann

#endif //LMS_H

