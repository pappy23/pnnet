#ifndef TRAINUTIL_H
#define TRAINUTIL_H

#include "Core/Includes.h"
#include "Core/Type.h"

namespace pann
{
    namespace TrainUtil
    {
        std::valarray<Float> squash_copy(const std::valarray<Float> & _v, Float _min, Float _max);
        void squash(std::valarray<Float> & _v, Float _min, Float _max);
    }; //TrainUtil
}; //pann

#endif

