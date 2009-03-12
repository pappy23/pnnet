/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

namespace pann
{
    namespace ActivationFunction
    {
        Base* Base::self = 0;
        int Base::refcount = 0;
    }; //ActivationFunction
}; //pann

