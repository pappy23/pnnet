/*
 * @file
 * Custom types declarations
 */

#ifndef TYPE_H
#define TYPE_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"

namespace pann
{
    typedef double Float;
    const Float inf = std::numeric_limits<Float>::infinity();

    typedef std::size_t HashType;

/**
 * Use case: ADD_PTR_TYPEDEF(Neuron)
 */
#define ADD_PTR_TYPEDEF(C) \
    typedef boost::shared_ptr<C> C##Ptr; \
    typedef boost::shared_ptr<const C> C##ConstPtr;


    class Neuron;
    ADD_PTR_TYPEDEF(Neuron);

    class Weight;
    ADD_PTR_TYPEDEF(Weight);
}; //pann

#endif //TYPE_H

