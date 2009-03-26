/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include "Includes.h"
#include "Type.h"
#include "Exception.h"

namespace pann
{
    namespace ActivationFunction
    {
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

            virtual std::string getName() const = 0;

            virtual Float f(Float) const = 0;
            virtual Float derivative(Float) const = 0;

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
			Linear() { };

        public:
			~Linear()
            {
                self = 0;
            };

        public:
            static Base* Instance()
            {
                if(!self)
                    self = new Linear();

                return self;
            };

            virtual std::string getName() const { return "Linear"; };

            virtual Float f(Float _x) const
            {
                return _x;
            } //f

            virtual Float derivative(Float) const
            {
                return 0;
            } //derivative

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
			Threshold() {};

        public:
			~Threshold() {};

        public:
            static Base* Instance()
            {
                if(!self)
                    self = new Threshold();

                return self;
            };

            virtual std::string getName() const { return "Threshold"; };

            virtual Float f(Float _x) const
            {
                if(_x < 0)
                    return 0;
                return 1;
            } //f

            virtual Float derivative(Float _x) const
            {
                if(_x == 0)
                    return inf;
                return 0;
            } //derivative

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
			TanH() {};

        public:
			~TanH() {};

        public:
            static Base* Instance()
            {
                if(!self)
                    self = new TanH();

                return self;
            };

            virtual std::string getName() const { return "TanH"; };

            virtual Float f(Float _x) const
            {
                return a * std::tanh( b * _x );
            } //f

            virtual Float derivative(Float) const
            {
                return 0;
            } //derivative
 
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

