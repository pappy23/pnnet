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
    class C; \
    typedef boost::shared_ptr<C> C##Ptr; \
    typedef boost::shared_ptr<const C> C##ConstPtr;


    ADD_PTR_TYPEDEF(Strategy);
    ADD_PTR_TYPEDEF(Runner);
    ADD_PTR_TYPEDEF(ActivationFunction);
    ADD_PTR_TYPEDEF(Neuron);
    ADD_PTR_TYPEDEF(Weight);
    ADD_PTR_TYPEDEF(Net);
    ADD_PTR_TYPEDEF(Attributes);
}; //pann

#endif //TYPE_H

