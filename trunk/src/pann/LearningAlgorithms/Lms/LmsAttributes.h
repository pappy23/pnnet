#ifndef LMSATTRIBUTES_H
#define LMSATTRIBUTES_H

#include "Core/Attributes.h"

namespace pann
{
    namespace LmsAttributes
    {
        const AttributeNameHash LMS = hash("LmsAttributes::LMS");
        const AttributeNameHash learningRate = hash("LmsAttributes::learningRate");
        const AttributeNameHash learningMomentum = hash("LmsAttributes::learningMomentum");
        const AttributeNameHash localGradient = hash("LmsAttributes::localGradient");
        const AttributeNameHash error = hash("LmsAttributes::error");
        const AttributeNameHash lastReceptiveField = hash("LmsAttributes::lastReceptiveField");
        const AttributeNameHash lastDeltaW = hash("LmsAttributes::lastDeltaW");
    }; //Attributes
}; //pann

#endif

