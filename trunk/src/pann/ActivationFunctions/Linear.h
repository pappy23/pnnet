#ifndef PANN_ACTIVATIONFUNCTIONS_LINEAR_H_INCLUDED
#define PANN_ACTIVATIONFUNCTIONS_LINEAR_H_INCLUDED

#include "Core/ActivationFunction.h"

namespace pann {
    /**
     * Linear function
     * y = x
     * dy/dx = 0
     */
    class Linear : public ActivationFunction
    {
        SINGLETON_SKELETON(Linear, ActivationFunction);

        virtual Float f(Float _x) const
        {
            return _x;
        }

        virtual Float derivative_dy(Float) const
        {
            return 1;
        }
    };
    REGISTER_SINGLETON_H(Linear);

}; //pann

#endif //PANN_ACTIVATIONFUNCTIONS_LINEAR_H_INCLUDED

