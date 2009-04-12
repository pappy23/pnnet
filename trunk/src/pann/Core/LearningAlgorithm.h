/**
 * @file
 * Abstract for all learning algorithms
 */

#ifndef LEARNINGALGORITHM_H
#define LEARNINGALGORITHM_H

#include "Includes.h"
#include "TrainData/TrainData.h"
#include "Net.h"

namespace pann
{
    class LearningAlgorithm
    {
    public:
        static void train(Net& _net, TrainData& _trainData);
    };

}; //pann

#endif

