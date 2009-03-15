/**
 * @file
 * Abstract for all network models
 */

#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include "Includes.h"
#include "Net.h"

namespace pann
{
    namespace NetworkModel
    {
        Net* MultilayerPerceptron(std::vector<unsigned> layers, ActivationFunction::Base* af, unsigned threads = 8);
    };

}; //pann

#endif

