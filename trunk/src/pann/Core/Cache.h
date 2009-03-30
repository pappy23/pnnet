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
    class Cache
    {
        /* Public interface */
    public:
        Cache();
        virtual ~Cache();

        virtual void flush() = 0;
        void touch();
        void fixed();
        bool isOk() const;

        /* Protected attributes */
    protected:
        bool coherent;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(coherent);
            };             
    };

}; //pann

#endif //CACHE_H

