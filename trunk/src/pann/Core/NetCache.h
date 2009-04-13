
#ifndef NETCACHE_H
#define NETCACHE_H

#include "Includes/BoostSerialization.h"

#include "Cache.h"

namespace pann
{
    class Neuron;

    class NetCache : public Cache
    {
        /* Public types */
    public:
        typedef std::vector<Neuron*> FrontType;

        /* Public members */
    public:
        std::vector<FrontType> layers;

        /* Public interface */
    public:
        virtual void flush() throw();

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Cache)
                   & BOOST_SERIALIZATION_NVP(layers);
            };             
    };
}; //pann

#endif

