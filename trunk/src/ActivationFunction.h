/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

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

            virtual float f(float) = 0;
            virtual float derivative(float) = 0;
        };

        /**
         * Linear function
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
        public:
            static Base& Instance()
            {
                if(!self)
                    self = new Linear();

                refcount++;

                return *self;
            };

            float f(float _x)
            {
                return _x;
            } //f

            float derivative(float)
            {
                return 0;
            } //derivative
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

