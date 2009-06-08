/**
 * @file
 * This file defines some attribute related staff and
 * declares common attributes groups and names
 *
 * README:
 * Every class derived from Object (@see Object.h)
 * has ability to use attributes
 * Object contains map<HashType, AttributesPtr>
 */
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Type.h"

using boost::hash;

namespace pann
{
    /**
     * Hasher
     * @param _name Readable name of attributes group
     * @return Unique integer hash value
     */
    HashType
    hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    }; //hash

    /**
     * Base class without instances
     */
    class Attributes
    {
    public:
        virtual ~Attributes();

        static const HashType getHash() { return groupName; };

    protected:
        Attributes()
        {
            groupName = hash("Derived class missed groupName initialization");
        };

    protected:
        static HashType groupName;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
            };

    }; //Attributes
    ADD_PTR_TYPEDEF(Attributes);

    /**
     * Attributes used in neurons to draw network model
     * in pann_viewer
     */
    class OpenGlAttributes : public Attributes
    {
    public:
        OpenGlAttributes()
            : r(0), g(0), b(0), x(0), y(0), z(0)
        {
            groupName = hash("OpenGlAttributes");
        };

        virtual ~OpenGlAttributes() {};

        unsigned char r, g, b; //Color
        signed int x, y, z; //Coordinates

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(x)
                & BOOST_SERIALIZATION_NVP(y)
                & BOOST_SERIALIZATION_NVP(z)
                & BOOST_SERIALIZATION_NVP(r)
                & BOOST_SERIALIZATION_NVP(g)
                & BOOST_SERIALIZATION_NVP(b);
            };
    }; //OpenGlAttributes
    ADD_PTR_TYPEDEF(OpenGlAttributes);

}; //pann

#endif
