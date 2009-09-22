//Weight.cpp

#include "Weight.h"

namespace pann
{
    Weight::Weight(Float _value)
        : value(_value), usageCount(0)
    {
    } //Weight

    Weight::~Weight()
    {
    } //~Weight

    Float
    Weight::getValue() const
    {
        return value;
    } //getValue

    void
    Weight::setValue(Float _value)
    {
        value = _value;
    } //setValue

    Float
    Weight::addValue(Float _delta)
    {
        value += _delta * 2.0 / Float(usageCount);

        return value;
    } //addValue

    unsigned
    Weight::getUsageCount() const
    {
        return usageCount;
    } //getUsageCount
    
    unsigned
    Weight::incUsageCount()
    {
        return ++usageCount;
    } //incUsageCount

    unsigned
    Weight::decUsageCount()
    {
        if(usageCount == 0)
            throw Exception()<<"Weight::decUsageCount(): negative usage count\n";

        return --usageCount;
    } //decUsageCount

    boost::mutex&
    Weight::getMutex()
    {
        return this->mutex;
    } //getMutex

}; //pann

