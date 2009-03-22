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
        /* Public interface */
    public:
        Cache() : coherent(false) { };
        virtual ~Cache() { };

        virtual void flush() = 0;

        void touch()
        {
            coherent = false;
        };
        
        void fixed()
        {
            coherent = true;
        };

        bool isOk() const
        {
            return coherent;
        };

        /* Protected attributes */
    protected:
        bool coherent;
    };

}; //pann

#endif //CACHE_H

