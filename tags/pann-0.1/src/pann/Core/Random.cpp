//Random.cpp

#include "Includes/BoostCommon.h"

#include "Random.h"

namespace pann
{
    Float
    rand(Float _min, Float _max)
    {
        static boost::lagged_fibonacci44497 engine;
        static boost::uniform_real<Float> distribution(0, 1);
        static boost::variate_generator<
            boost::lagged_fibonacci44497,
            boost::uniform_real<Float>
        > generator(engine, distribution);

        //Generate v from (0; 1) and squash it to (_min; _max) range
        Float v = generator();
        Float a = ( _max - _min );
        Float b = _max - a;
        v = a * v + b;

        return v;
    } //rand

}; //pann

