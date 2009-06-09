//ActivationFunction.cpp

#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::Linear);
BOOST_CLASS_EXPORT(pann::Threshold);
BOOST_CLASS_EXPORT(pann::TanH);

namespace pann
{
    //Registering singletons
    bool register_activation_functions()
    {
        Linear::Instance();
        Threshold::Instance();
        TanH::Instance();
		return true; //TODO: check this, add only for building
    } //register_activation_functions

    const bool activation_functions_registration_result = register_activation_functions();
}; //pann

