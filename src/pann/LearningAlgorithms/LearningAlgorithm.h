/**
 * @file
 * Abstract for all learning algorithms
 */

#ifndef LEARNINGALGORITHM_H
#define LEARNINGALGORITHM_H

#include "Core/Type.h"

namespace pann
{
    class TrainData;

    class LearningAlgorithm
    {
    public:
        static void train(NetPtr _net, TrainData& _trainData);
    };

    void test(NetPtr _net, TrainData& _td);

}; //pann

#endif

