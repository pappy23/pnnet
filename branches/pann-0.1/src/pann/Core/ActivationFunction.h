/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include "Includes/BoostSerialization.h"

#include "Type.h"

namespace pann
{
    /**
     * All activation functions inherit ActivationFunction::ActivationFunction
     * and implement Instance() method
     */
    class ActivationFunction
    {
    public:
        virtual Float f(Float) const = 0;
        virtual Float derivative_dy(Float) const = 0;
    };

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

#endif //ACTIVATIONFUNCTION_H

