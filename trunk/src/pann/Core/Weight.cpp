//Weight.cpp

#include "Weight.h"

namespace pann
{
    const AttributeName Weight::value = hash("Weight::value", NativeParameters);

    Weight::Weight(Float _value) throw()
    {
        (*this)[value] = _value;
        usageCount = 0;
    } //Weight

    Weight::~Weight() throw()
    {
    } //~Weight

}; //pann

