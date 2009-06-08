/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include "Includes/BoostSerialization.h"

#include "Type.h"

using boost::shared_ptr;

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
        //Singleton
        Linear() {};

    public:
        static ActivationFunctionPtr Instance()
        {
            static ActivationFunctionPtr self(new Linear());
            return self;
        }

        virtual Float f(Float _x) const
        {
            return _x;
        }

        virtual Float derivative_dy(Float) const
        {
            return 1;
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<Linear, ActivationFunction>(
                    static_cast<Linear*>(NULL),
                    static_cast<ActivationFunction*>(NULL));
            };
    };

    /**
     * MacCalloc-Pitz threshold function
     * y = 0, x <0
     * y = 1, x>=0
     */
    class Threshold : public ActivationFunction
    {
        //Singleton
        Threshold() {};

    public:
        static ActivationFunctionPtr Instance()
        {
            static ActivationFunctionPtr self(new Threshold());
            return self;
        }

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

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<Threshold, ActivationFunction>(
                    static_cast<Threshold*>(NULL),
                    static_cast<ActivationFunction*>(NULL));
            };
    };

    /**
     * Hyperbolic tangent function
     * y = a*tanh(b*x)
     */
    class TanH : public ActivationFunction
    {
        //Singleton
        TanH() : a( 1.7179 ), b( 2.0 / 3.0 ) {};

    public:
        static ActivationFunctionPtr Instance()
        {
            static ActivationFunctionPtr self(new TanH());
            return self;
        }

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

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<TanH, ActivationFunction>(
                    static_cast<TanH*>(NULL),
                    static_cast<ActivationFunction*>(NULL));
            };
    };

}; //pann
#endif //ACTIVATIONFUNCTION_H

