//Weight.cpp

#include "Weight.h"

namespace pann
{
    const AttributeName Weight::value = hash("Weight::value", NativeParameters);

    Weight::Weight(Float _value, unsigned _usageCount) throw()
    {
        (*this)[value] = _value;
        usageCount = _usageCount;
    } //Weight

    Weight::~Weight() throw()
    {
    } //~Weight

}; //pann

