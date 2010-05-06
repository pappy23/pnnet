/**
 * @file
 * Runtime cache object
 */

#ifndef PANN_CORE_CACHE_H_INCLUDED
#define PANN_CORE_CACHE_H_INCLUDED

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

        void touch()
        {
            coherent = false;
        };

        void fixed()
        {
            coherent = true;
        };

        bool is_ok() const
        {
            return coherent;
        };

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
    }; //Cache

}; //pann

#endif //PANN_CORE_CACHE_H_INCLUDED

