//ActivationFunction.cpp

#include "Includes/BoostSerialization.h"
#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::Linear);

const pann::ActivationFunctionPtr LinearRegister = pann::Linear::Instance();
