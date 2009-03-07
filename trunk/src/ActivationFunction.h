//ActivationFunction.h

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

namespace pann
{
    namespace ActivationFunction
    {
        class Base //Singleton
        {
        protected:
            static Base* self;
            static int refcount;

        public:
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

