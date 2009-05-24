#ifndef MULTILAYERPERCEPTRON_H
#define MULTILAYERPERCEPTRON_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Core/ActivationFunction.h"

namespace pann
{
    class Net;

    /*
     * Function construct Multilayer perceptron with full connectivity between layers
     * Takes vector of tuples. Each tuple describes how many neurons should constructor place
     * at each layer and what activation function use in neurons
     * If activation function isn't set, TanH will be used
     */
    Net& MultilayerPerceptron(std::vector<boost::tuple<unsigned, ActivationFunction::Base*> > _layers);

}; //pann

#endif

