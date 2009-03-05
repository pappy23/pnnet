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
        Weight(float) : 
            value(value),
            usageCount(1) { };

        ~Weight() { };

        int usageCount;
        float value;
    };

}; //pann

#endif //WEIGHT_H

