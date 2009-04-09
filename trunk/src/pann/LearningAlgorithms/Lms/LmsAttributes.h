#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/Attributes.h"

namespace pann
{
    namespace LmsAttributes
    {
        //Net
        const AttributeNameHash LMS = hash("LmsAttributes::LMS");
        const AttributeNameHash learningRate = hash("LmsAttributes::learningRate"); //Weight can override
        const AttributeNameHash learningMomentum = hash("LmsAttributes::learningMomentum"); //Weight can override

        //Neuron
        const AttributeNameHash lastReceptiveField = hash("LmsAttributes::lastReceptiveField");
        const AttributeNameHash error = hash("LmsAttributes::error");
        const AttributeNameHash localGradient = hash("LmsAttributes::localGradient");

        //Weight
        const AttributeNameHash lastDeltaW = hash("LmsAttributes::lastDeltaW");
    }; //Attributes
}; //pann

#endif

