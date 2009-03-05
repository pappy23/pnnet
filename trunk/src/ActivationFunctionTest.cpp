#include <iostream>

#include "ActivationFunction.h"

using namespace pann;

int main()
{
    ActivationFunctions::Linear F;
    std::cout<<F.f(5)<<std::endl;
    return 0;
}
