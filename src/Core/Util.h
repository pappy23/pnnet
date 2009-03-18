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
        };
        
        bool operator()(const ConstNeuronIter& _lhs, const ConstNeuronIter& _rhs) const
        {
            return _lhs->first < _rhs->first;
        };
        
        static bool equal(const NeuronIter& _lhs, const NeuronIter& _rhs) 
        {
            return _lhs->first == _rhs->first;
        }
    };
}; //pann

#endif //UTIL_H 
