/**
 * @file
 * This file defines some attribute related staff and 
 * declares common attributes groups and names
 * 
 * README:
 * Every class derived from Object (see Object.h)
 * has ability to use attributes (only Float type at the moment)
 * Object contains map<AttributeName, AttributeType>
 * AttributeName consists from name and group_name
 * It allows erasing of entire group at once, for ex. LearningParameters
 *
 * TODO:
 * Replace AttributeType == Float with boost::tuple ?
 * Get rid of custom Attributes and use boost::property_map instead ?
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Includes/BoostSerialization.h"

#include "Type.h"

namespace pann
{
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
    
    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs);

    typedef Float AttributeType;

    HashType hash(const char* _name);
    AttributeName hash(const char* _name, HashType _group);

    //Registered group names
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

