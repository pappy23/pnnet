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
        virtual void train(Net& _net, TrainData _trainData, int t) = 0;
    };

}; //pann

#endif

