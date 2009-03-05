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
            static float f(float);
            static float derivative(float);
        };

        class Linear : public Base
        {
        public:
            static float f(float x)
            {
                return x;
            } //f

            static float derivative(float)
            {
                return 0;
            } //derivative
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

