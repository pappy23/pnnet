
#ifndef TRAINDATAGENERATOR_H
#define TRAINDATAGENERATOR_H

#include "Core/Includes.h"
#include "Core/Type.h"
#include "Core/Util.h"
#include "TrainData.h"

namespace pann
{
    namespace DataGenerator
    {
        TrainData* generateFromFunction(Float _min, Float _max, unsigned _count, boost::function<Float (Float _x)> _f);
    }; //DataGenerator
}; //pann

#endif

