
#ifndef NETCACHE_H
#define NETCACHE_H

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Cache.h"

namespace pann
{
    class Neuron;

    class NetCache : public Cache
    {
        /* Public types */
    public:
        typedef std::vector<boost::shared_ptr<Neuron> > FrontType;

        /* Public members */
    public:
        //TODO: Should we hide internal details from user?
        std::vector<FrontType> layers;

        /* Public interface */
    public:
        virtual void flush();

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

