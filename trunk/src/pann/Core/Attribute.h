#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Includes.h"
#include "Type.h"

namespace pann
{
    typedef std::size_t HashType;

    class AttributeName
    {
    public:
        HashType name;
        HashType group;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 ar & BOOST_SERIALIZATION_NVP(name)
                    & BOOST_SERIALIZATION_NVP(group);
            };
    };
    
    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs) throw();

    typedef Float AttributeType;

    HashType hash(const char* _name) throw();
    AttributeName hash(const char* _name, HashType _group) throw();

    //Registered group names
    const HashType NativeParameters = hash("NativeParameters");
    const HashType OpenGlParameters = hash("OpenGlParameters");
    const HashType AlgorithmSpecificLearningParameters = hash("AlgorithmSpecificLearningParameters");

    //Parameters related to pann_viewer
    namespace OpenGlAttributes
    {
        const AttributeName color_r = hash("color_r", OpenGlParameters);
        const AttributeName color_g = hash("color_g", OpenGlParameters);
        const AttributeName color_b = hash("color_b", OpenGlParameters);
        const AttributeName coord_x = hash("coord_x", OpenGlParameters);
        const AttributeName coord_y = hash("coord_y", OpenGlParameters);
        const AttributeName coord_z = hash("coord_z", OpenGlParameters);
    }; //OpenGlAttributes

}; //pann

#endif

