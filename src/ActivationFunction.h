//ActivationFunction.h

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

namespace pann
{
    namespace ActivationFunction
    {
        class Base
        {
        public:
            virtual float f(float) = 0;
            virtual float derivative(float) = 0;
        };

        class Linear : public Base
        {
        public:
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

