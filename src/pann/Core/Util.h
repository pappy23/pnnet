#ifndef UTIL_H
#define UTIL_H

#include "Includes.h"
#include "Type.h"
#include "Net.h"

namespace pann
{
    namespace Util
    {
        std::valarray<Float> squash_copy(const std::valarray<Float> & _v, Float _min, Float _max) throw();
        void squash(std::valarray<Float> & _v, Float _min, Float _max) throw();

        Float rand(Float _min, Float _max) throw();
        void randomizeWeightsGauss(Net& _net, Float _min, Float _max) throw();
    }; //Util
}; //pann

#endif

