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

            virtual unsigned getId() const = 0;
            virtual std::string getName() const = 0;

            virtual Float f(Float) const = 0;
            virtual Float derivative(Float) const = 0;
        };

        /**
         * Linear function
         * id = 1
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
        private:
            static Base* self;

		private:
			Linear() {};

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

            virtual unsigned getId() const { return 1; };
            virtual std::string getName() const { return "Linear"; };

            virtual Float f(Float _x) const
            {
                return _x;
            } //f

            virtual Float derivative(Float) const
            {
                return 0;
            } //derivative
        };

        /**
         * MacCalloc-Pitz threshold function
         * id = 2
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

            virtual unsigned getId() const { return 2; };
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
        };

        /**
         * Hyperbolic tangent function
         * id = 3
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

            virtual unsigned getId() const { return 3; };
            virtual std::string getName() const { return "TanH"; };

            virtual Float f(Float _x) const
            {
                return a * std::tanh( b * _x );
            } //f

            virtual Float derivative(Float) const
            {
                return 0;
            } //derivative
        };

        /*
         * ADD NEW FUNCTIONS TO getById()
         */
        Base* getById(const unsigned id);

    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

