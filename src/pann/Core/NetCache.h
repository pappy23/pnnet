
#ifndef PANN_CORE_NETCACHE_H_INCLUDED
#define PANN_CORE_NETCACHE_H_INCLUDED

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Type.h"
#include "Cache.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Neuron);

    class NetCache : public Cache
    {
    public:
        typedef std::vector<NeuronPtr> Front;

        //TODO: Should we hide internal details from user?
        //Solutions:
        //1)Write restricted interface to layers
        //2)Derive NetCache from Cache AND vector<FrontType>
        //3)write const vector<const FrontType> NetCache::layers() - current solution
        std::vector<Front> layers;

        virtual void flush()
        {
            layers.clear();
            touch();
        };

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Cache)
                   & BOOST_SERIALIZATION_NVP(layers);
            };
    }; //NetCache
}; //pann

#endif //PANN_CORE_NETCACHE_H_INCLUDED

