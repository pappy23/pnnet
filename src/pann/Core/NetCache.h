
#ifndef NETCACHE_H
#define NETCACHE_H

#include "Includes.h"
#include "Cache.h"
#include "Neuron.h"

namespace pann
{
    class NetCache : public Cache
    {
        /* Public types */
    public:
        typedef std::vector<Neuron*> ThreadTaskType;
        typedef std::vector<ThreadTaskType> FrontType;

        /* Public members */
    public:
        std::vector<FrontType> data;

        /* Public interface */
    public:
        virtual void flush() throw();

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(coherent);
                ar & BOOST_SERIALIZATION_NVP(data);
            };             
    };
}; //pann

#endif

