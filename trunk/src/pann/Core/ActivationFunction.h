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
        void boost_export();

        /**
         * All activation functions inherit ActivationFunction::Base
         * and implement Instance() method
         * Base is a singleton pattern
         */
        class Base //Singleton
        {
        public:
            //Returns reference to ActivationFunction object. It is always the same
            //Only one object of class Base exist at a time
            static Base* Instance();

            virtual Float f(Float) const = 0;
            virtual Float derivative_dy(Float) const = 0;

        /* Serialization */
        private:
            friend class boost::serialization::access;
        };

        /**
         * Linear function
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
        private:
            static Base* self;

		private:
			Linear();

        public:
			~Linear();

        public:
            static Base* Instance();
            virtual Float f(Float _x) const;
            virtual Float derivative_dy(Float) const;

            /* Serialization */
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
        private:
            static Base* self;

		private:
			Threshold();

        public:
			~Threshold();

        public:
            static Base* Instance();
            virtual Float f(Float _x) const;
            virtual Float derivative_dy(Float) const;

            /* Serialization */
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
        private:
            static Base* self;

        public:
            static const Float a;
            static const Float b;

		private:
			TanH();

        public:
			~TanH();

        public:
            static Base* Instance();
            virtual Float f(Float _x) const;
            virtual Float derivative_dy(Float) const;
 
            /* Serialization */
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

    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

