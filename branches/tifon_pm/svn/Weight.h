//Weight.h

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Includes.h"
#include "Object.h"

namespace pann
{

    class Weight : public Object
    {
    public:
        int usageCount;
        float value;

        Weight(float value = 1) : 
            value(value),
            usageCount(1) { };

        ~Weight() { };
    };

}; //pann

#endif //WEIGHT_H

