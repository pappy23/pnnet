//util.cpp

#include <cstdlib>
#include <iostream>
#include "pann.h"
#include "util.h"

using std::srand;

void random_seed(unsigned seed)
{
    if(0 != seed) {
        srand(seed);
    }
    pann::seed(seed);
    std::cout<<"Reset RNG to "<<seed<<"\n";
}; //random_seed

