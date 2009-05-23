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
     * Uses boost::random
     */
    Float rand(Float _min, Float _max);

}; //pann

#endif //RANDOM_H

