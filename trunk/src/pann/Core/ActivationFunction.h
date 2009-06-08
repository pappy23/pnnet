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
    class Neuron;

    namespace ActivationFunction
    {
        /**
         * All activation functions inherit ActivationFunction::Base
         * and implement Instance() method
         */
        class Base
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
        class Linear : public Base
        {
            //Singleton
			Linear() {};
			virtual ~Linear() {};

        public:
            static Base* Instance()
            {
                static Base* self = new Linear();
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
                     boost::serialization::void_cast_register<Linear, Base>(
                        static_cast<Linear*>(NULL),
                        static_cast<Base*>(NULL));
                };
        };

        /**
         * MacCalloc-Pitz threshold function
         * y = 0, x <0
         * y = 1, x>=0
         */
        class Threshold : public Base
        {
            //Singleton
			Threshold() {};
			virtual ~Threshold() {};

        public:
            static Base* Instance()
            {
                static Base* self = new Threshold();
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
                     boost::serialization::void_cast_register<Threshold, Base>(
                        static_cast<Threshold*>(NULL),
                        static_cast<Base*>(NULL));
                };
        };

        /**
         * Hyperbolic tangent function
         * y = a*tanh(b*x)
         */
        class TanH : public Base
        {
            //Singleton
			TanH() : a( 1.7179 ), b( 2.0 / 3.0 ) {};
			virtual ~TanH() {};

        private:
            const Float a;
            const Float b;

        public:
            static Base* Instance()
            {
                static Base* self = new TanH();
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
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                     boost::serialization::void_cast_register<TanH, Base>(
                        static_cast<TanH*>(NULL),
                        static_cast<Base*>(NULL));
                };
        };

    }; //ActivationFunction

}; //pann
#endif //ACTIVATIONFUNCTION_H

