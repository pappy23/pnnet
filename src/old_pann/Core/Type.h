/*
 * @file
 * Custom types declarations
 */

#ifndef PANN_CORE_TYPE_H_INCLUDED
#define PANN_CORE_TYPE_H_INCLUDED

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Macros.h"

namespace pann
{
    typedef double Float;
    const Float inf = std::numeric_limits<Float>::infinity();

    typedef std::size_t HashT;

    /**
     * Hasher
     * @param _name Readable name of attributes group
     * @return Unique integer hash value
     */
    inline HashT hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    }; //hash

}; //pann

#endif //PANN_CORE_TYPE_H_INCLUDED

