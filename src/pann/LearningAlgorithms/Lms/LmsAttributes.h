#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/AttributesDeclaration.h"
#include "Core/AttributesManager.h"

using namespace pann::AttributesDeclaration;

namespace pann
{
    namespace LmsAttributes
    {
        //Net
        const AttributeName LMS = {
            hash("LMS"),
            AlgorithmSpecificLearningParameters
        };
        const AttributeName learningRate = {
            hash("learningRate"),
            CommonLearningParameters
        }; //Weight can override
        const AttributeName learningMomentum = {
            hash("LmsAttributes::learningMomentum"),
            AlgorithmSpecificLearningParameters
        }; //Weight can override

        //Neuron
        const AttributeName lastReceptiveField = { 
            hash("LmsAttributes::lastReceptiveField"), 
            AlgorithmSpecificLearningParameters 
        };
        const AttributeName error = {
            hash("LmsAttributes::error"),
            AlgorithmSpecificLearningParameters
        };
        const AttributeName localGradient = {
            hash("LmsAttributes::localGradient"),
            AlgorithmSpecificLearningParameters
        };
        
        //Weight
        const AttributeName lastDeltaW = {
            hash("LmsAttributes::lastDeltaW"),
            AlgorithmSpecificLearningParameters
        };
    }; //Attributes
}; //pann

#endif

