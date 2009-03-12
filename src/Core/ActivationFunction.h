/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include "Includes.h"
#include "Type.h"

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
        protected:
            static boost::shared_ptr<Base> self;

        protected:
			Base() { };

        public:
			virtual ~Base() { };

        public:
            //Returns reference to ActivationFunction object. It is always the same
            //Only one object of class Base exist at a time
            static boost::shared_ptr<Base> Instance();

            virtual Float f(Float) = 0;
            virtual Float derivative(Float) = 0;
        };

        /**
         * Linear function
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
		private:
			Linear() {};

        public:
			~Linear() {};

        public:
            static boost::shared_ptr<Base> Instance()
            {
                if(!self)
                    self = boost::shared_ptr<Base>(new Linear());

                return self;
            };

            Float f(Float _x)
            {
                return _x;
            } //f

            Float derivative(Float)
            {
                return 0;
            } //derivative
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

