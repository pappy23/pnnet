#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/Attribute.h"

namespace pann
{
    namespace LmsAttributes
    {
        //Net
        const AttributeName LMS = hash("LmsAttributes::LMS", AlgorithmSpecificLearningParameters);
        const AttributeName learningRate = hash("LearningAlgorithm::learningRate", AlgorithmSpecificLearningParameters);
        const AttributeName learningMomentum = hash("LmsAttributes::learningMomentum", AlgorithmSpecificLearningParameters);
        const AttributeName epoch = hash("LmsAttributes::epoch", AlgorithmSpecificLearningParameters);
        const AttributeName annealingTSC = hash("LmsAttributes::annealingTSC", AlgorithmSpecificLearningParameters);

        //Neuron
        const AttributeName error = hash("LmsAttributes::error", AlgorithmSpecificLearningParameters);
        const AttributeName localGradient = hash("LmsAttributes::localGradient", AlgorithmSpecificLearningParameters);
        
        //Weight
        const AttributeName lastDeltaW = hash("LmsAttributes::lastDeltaW", AlgorithmSpecificLearningParameters);

    }; //Attributes
}; //pann

#endif

