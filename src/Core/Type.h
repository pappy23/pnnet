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
	typedef unsigned int UINT;

    class Neuron;
    typedef std::map<int, Neuron>::iterator NeuronIter;

}; //pann

#endif //TYPE_H

