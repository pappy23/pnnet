
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

        Float operator[] (Hash key)
        {
            return m_attribute_map[key];
        };

        Float get_attr(Hash key) const;
        void set_attr(Hash key, Float value);

    protected:
        std::map<Hash, Float> mutable m_attribute_map;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(m_attribute_map);
            };
    }; //Object
    ADD_PTR_TYPEDEF(Object);

}; //pann

#endif //PANN_CORE_OBJECT_H_INCLUDES

