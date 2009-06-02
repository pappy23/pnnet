/**
 * Random number generators
 */

#ifndef RANDOM_H
#define RANDOM_H

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
     * Uses rand01(), but interpolates it to range [_min; _max]
     */
    Float rand(Float _min, Float _max);

    /**
     * Drop coin with specified probability
     */
    bool rand(Float _probability = 0.5);

}; //pann

#endif //RANDOM_H

