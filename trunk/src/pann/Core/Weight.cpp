//Weight.cpp

#include "Weight.h"

namespace pann
{
    Weight::Weight(Float _value) throw()
    {
        value = _value;
        usageCount = 0;
    } //Weight

    Weight::~Weight() throw()
    {
    } //~Weight

}; //pann

