//LMS.cpp

#include "LMS.h"

BOOST_SERIALIZATION_FACTORY_0(pann::LearningHint::LmsNet)
BOOST_SERIALIZATION_FACTORY_0(pann::LearningHint::LmsNeuron)
BOOST_CLASS_EXPORT(pann::LearningHint::LmsNet);
BOOST_CLASS_EXPORT(pann::LearningHint::LmsNeuron);

namespace pann
{
    Runner* LmsFeedforwardRunner::self = 0;
    Runner* LmsBackpropagationRunner::self = 0;
}; //pann

