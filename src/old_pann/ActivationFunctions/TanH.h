#ifndef PANN_ACTIVATIONFUNCTIONS_TANH_H_INCLUDED
#define PANN_ACTIVATIONFUNCTIONS_TANH_H_INCLUDED

#include "Core/ActivationFunction.h"

namespace pann {
    /**
     * Hyperbolic tangent function
     * y = a*tanh(b*x)
     */
    class TanH : public ActivationFunction
    {
        TanH() : a( 1.7179 ), b( 2.0 / 3.0 ) {};
        SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(TanH, ActivationFunction);

        virtual Float f(Float _x) const
        {
            return a * std::tanh( b * _x );
        }

        virtual Float derivative_dy(Float _y) const
        {
            return b/a * (a - _y) * (a + _y);
        }

    private:
        const Float a;
        const Float b;
    };
    REGISTER_SINGLETON_H(TanH);

}; //pann

#endif //PANN_ACTIVATIONFUNCTIONS_TANH_H_INCLUDED

