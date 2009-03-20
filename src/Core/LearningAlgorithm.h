/**
 * @file
 * Abstract for all learning algorithms
 */

#ifndef LEARNINGALGORITHM_H
#define LEARNINGALGORITHM_H

#include "Includes.h"
#include "Net.h"
#include "TrainData.h"

namespace pann
{
    class LearningAlgorithm
    {
    public:
        virtual void train(Net& _net, TrainData _trainData) = 0;
    };

}; //pann

#endif

