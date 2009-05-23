//MultilayerPerceptron.cpp

#include "Core/Includes/Std.h"
#include "Core/Includes/BoostCommon.h"
#include "Core/ActivationFunction.h"

namespace pann
{
    class Net;

    namespace NetworkModel
    {
        /*
         * TODO: write documentation
         */
        Net& MultilayerPerceptron(std::vector<unsigned> layers, ActivationFunction::Base* af);
    };

}; //pann

