/**
 * @file
 * Abstract for all learning algorithms
 */

#ifndef LEARNINGALGORITHM_H
#define LEARNINGALGORITHM_H

namespace pann
{
    class Net;
    class TrainData;

    class LearningAlgorithm
    {
    public:
        static void train(Net& _net, TrainData& _trainData);
    };

}; //pann

#endif

