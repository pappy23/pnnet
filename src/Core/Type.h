/*
 * @file
 * Custom types declarations
 */

#ifndef TYPE_H
#define TYPE_H

#include "Includes.h"

namespace pann
{
    typedef double Float;
    const Float inf = std::numeric_limits<double>::infinity();

	typedef unsigned int UINT;
	typedef unsigned int uint;

    class Neuron;
    typedef std::map<int, Neuron>::iterator NeuronIter;

    class Weight;
    typedef std::map<int, Weight>::iterator WeightIter;

}; //pann

#endif //TYPE_H

