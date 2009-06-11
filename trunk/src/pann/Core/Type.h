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
     * Hasher
     * @param _name Readable name of attributes group
     * @return Unique integer hash value
     */
    inline HashType
    hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    }; //hash

/**
 * Use case: ADD_PTR_TYPEDEF(Neuron)
 */
#define ADD_PTR_TYPEDEF(C) \
    class C; \
    typedef boost::shared_ptr<C> C##Ptr; \
    typedef boost::shared_ptr<const C> C##ConstPtr;

    ADD_PTR_TYPEDEF(Runner);
    ADD_PTR_TYPEDEF(ActivationFunction);
    ADD_PTR_TYPEDEF(Neuron);
    ADD_PTR_TYPEDEF(Weight);
    ADD_PTR_TYPEDEF(Net);
    ADD_PTR_TYPEDEF(Attributes);

}; //pann

#endif //TYPE_H

