/**
 * @file
 * Runtime cache object
 */

#ifndef CACHE_H
#define CACHE_H

#include "Includes/BoostSerialization.h"

namespace pann
{
    /**
     * Abstract cache object
     * In reality every class should inherit own SuperDuperCache from this class
     */
    class Cache
    {
    public:
        Cache() : coherent(false) {};
        virtual ~Cache() {};

        virtual void flush() = 0;
        void touch() { coherent = false; };
        void fixed() { coherent = true;  };
        bool isOk() const { return coherent; };

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

