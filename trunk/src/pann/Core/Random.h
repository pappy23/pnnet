/**
 * Random number generators
 */

#ifndef PANN_CORE_RANDOM_H_INCLUDED
#define PANN_CORE_RANDOM_H_INCLUDED

#include <boost/random.hpp> 
#include "Core/Type.h"

namespace pann
{
    /**
     * Very cool pseudorandom number generator
     * Returns good random number in [0.0; 1.0] range
     * Uses boost::random
     */
    Float rand01();

    /**
     * Uses rand01(), but scales it to range [_min; _max]
     */
    Float rand(Float _min, Float _max);

    /**
     * Drop coin with specified probability
     */
    bool rand_coin(Float _probability = 0.5);

}; //pann

#endif //PANN_CORE_RANDOM_H_INCLUDED

