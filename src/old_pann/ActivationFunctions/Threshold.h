#ifndef PANN_ACTIVATIONFUNCTIONS_THRESHOLD_H_INCLUDED
#define PANN_ACTIVATIONFUNCTIONS_THRESHOLD_H_INCLUDED

#include "Core/ActivationFunction.h"

namespace pann {
    /**
     * MacCalloc-Pitz threshold function
     * y = 0, x <0
     * y = 1, x>=0
     */
    class Threshold : public ActivationFunction
    {
        SINGLETON_SKELETON(Threshold, ActivationFunction);

        virtual Float f(Float _x) const
        {
            if(_x < 0)
                return 0;
            return 1;
        }

        virtual Float derivative_dy(Float _y) const
        {
            if(_y == 0)
                return inf;

            return 0;
        }
    };
    REGISTER_SINGLETON_H(Threshold);

}; //pann

#endif //PANN_ACTIVATIONFUNCTIONS_THRESHOLD_H_INCLUDED

