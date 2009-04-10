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

        /**
         * Assign initial weights from interval [_min; _max]
         */
        void randomizeWeightsGauss(Net& _net, Float _min = -0.3, Float _max = +0.3) throw();

        /**
         * Weight is random number from [_min/sqrt(C); _max/sqrt(C)]
         * C - number of inputs in current neuron
         * _min = -2.4, _max = 2.4 is good choise
         * See Gradien-Based Learning Applied to Document Recognition, Yann LeCun, app1, p.41
         * See S. Haykin, p252
         */
        void randomizeWeightsAccordingToInputsCount(Net& _net, Float _min = -2.4, Float _max = +2.4) throw();
    }; //Util
}; //pann

#endif

