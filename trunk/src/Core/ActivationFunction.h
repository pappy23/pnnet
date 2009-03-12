/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

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
            static Base* self;
            static int refcount;
			Base() {};
			virtual ~Base() {};

        public:
            //Returns reference to ActivationFunction object. It is always the same
            //Only one object of class Base exist at a time
            static Base& Instance();
            void freeInstance()
            {
                refcount--;
                if(!refcount)
                {
                    delete this;
                    self = 0;
                }
            };

            virtual FLOAT f(FLOAT) = 0;
            virtual FLOAT derivative(FLOAT) = 0;
        };

        /**
         * Linear function
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
		protected:
			Linear() {};
			~Linear() {};
        public:
            static Base& Instance()
            {
                if(!self)
                    self = new Linear();

                refcount++;

                return *self;
            };

            FLOAT f(FLOAT _x)
            {
                return _x;
            } //f

            FLOAT derivative(FLOAT)
            {
                return 0;
            } //derivative
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

