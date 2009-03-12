/*
 * @file
 * Various utils
 */

#ifndef UTIL_H
#define UTIL_H

#include "Includes.h"

namespace pann
{
    struct NeuronIterCompare
    {
        bool operator()(const NeuronIter& _lhs, const NeuronIter& _rhs) const
        {
            return _lhs->first < _rhs->first;
        }
    };

}; //pann

#endif //UTIL_H 
