/**
 * @file
 * Activation functions interface
 */

#ifndef PANN_CORE_ACTIVATIONFUNCTION_H_INCLUDED
#define PANN_CORE_ACTIVATIONFUNCTION_H_INCLUDED

#include "Type.h"

namespace pann
{
    /**
     * All activation functions inherit ActivationFunction
     * and implement Instance() method
     */
    class ActivationFunction
    {
    public:
        virtual Float f(Float) const = 0;
        virtual Float derivative_dy(Float) const = 0;
    };

}; //pann

#endif //PANN_CORE_ACTIVATIONFUNCTION_H_INCLUDED

