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
    const Float inf = std::numeric_limits<Float>::infinity();

	typedef unsigned int UINT;
	typedef unsigned int uint;

    class Neuron;
    typedef std::map<unsigned, Neuron>::iterator NeuronIter;
    typedef std::map<unsigned, Neuron>::const_iterator ConstNeuronIter;

    class Weight;
    typedef std::map<unsigned, Weight>::iterator WeightIter;
    typedef std::map<unsigned, Weight>::const_iterator ConstWeightIter;

}; //pann

#endif //TYPE_H

