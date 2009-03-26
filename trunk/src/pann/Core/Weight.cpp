//Weight.cpp

#include "Weight.h"

namespace pann
{
    Weight::Weight(Float _value)
    {
        value = _value;
        usageCount = 0;
    } //Weight

    Weight::~Weight()
    {
    } //~Weight

}; //pann

#endif //WEIGHT_H

