/**
 * @file
 * Runtime cache object
 */

#ifndef CACHE_H
#define CACHE_H

#include "Includes.h"
#include "Object.h"

namespace pann
{

    /**
     * Abstract cache object
     * In reality every class should inherit own SuperDuperCache from this class
     */
    class Cache : public Object
    {
    protected:
        bool coherent;

    public:
        Cache() : coherent(false) { };
        virtual ~Cache() { };

        virtual void flush() = 0;

        inline void touch() { coherent = false; };
        inline void fixed() { coherent = true;  };
        inline bool isOk() { return coherent; };
        inline bool isUp2Date() { return isOk(); };
        inline bool isCoherent() { return isOk(); };
    };

}; //pann

#endif //CACHE_H

