/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::ActivationFunction::Linear);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Threshold);
BOOST_CLASS_EXPORT(pann::ActivationFunction::TanH);

namespace pann
{
    namespace ActivationFunction
    {
        Base* Linear::self = 0;
        Base* Threshold::self = 0;
        Base* TanH::self = 0;

        const Float TanH::a = 1.7159;
        const Float TanH::b = 0.6667;
    }; //ActivationFunction
}; //pann

