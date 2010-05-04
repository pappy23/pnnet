
#ifndef PANN_CORE_OBJECT_H_INCLUDES
#define PANN_CORE_OBJECT_H_INCLUDES

#include "Includes/BoostSerialization.h"
#include "Type.h"

namespace pann
{
    class Object
    {
    public:
        Object() {};
        virtual ~Object() {};

        std::map<Hash, Float> mutable attribute_map;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(attribute_map);
            };
    }; //Object
    ADD_PTR_TYPEDEF(Object);

}; //pann

#endif //PANN_CORE_OBJECT_H_INCLUDES

