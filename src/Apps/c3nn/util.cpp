//util.cpp

#include <cstdlib>
#include "util.h"

using std::srand;

void random_seed(unsigned seed)
{
    if(0 != seed)
        srand(seed);
}; //random_seed

