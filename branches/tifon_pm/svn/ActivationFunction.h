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
            static Base* _self;  //FIX: this is pointer!
            static int _refcount;

        public:
            static Base* Instance(); //FIX: return pointer
            void freeInstance()
            {
                _refcount--;
                if(!_refcount)
                {
                    delete this;
                    _self = 0;
                }
            };

            virtual float f(float) = 0;
            virtual float derivative(float) = 0;
        };

//FIX: Init this in ActivationFunction.cpp
//        Base* Base::_self = 0;
//        int Base::_refcount = 0;

        class Linear : public Base
        {
        public:
            static Base* Instance()
            {
                if(!_self)
                    _self = new Linear();

                _refcount++;

                return _self; //FIX: return poiner
            };

            float f(float x)
            {
                return x;
            } //f

            float derivative(float)
            {
                return 0;
            } //derivative
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

