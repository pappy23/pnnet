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
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Includes/BoostSerialization.h"

#include "Type.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Attributes);
    ADD_PTR_TYPEDEF(OpenGlAttributes);

    HashType hash(const char* _name);

    namespace AttributesGroup
    {
        const HashType OpenGl = hash("OpenGlAttributes");
        //const HashType Learning = hash("LearningAlgorithmAttributes");
    }; //AttributesGroup

    class Attributes
    {
    public:
        Attributes();
        virtual ~Attributes();

        virtual HashType getName() = 0;

    private:
        friend class boost::serialization::access;
    }; //Attributes

    class OpenGlAttributes : public Attributes
    {
    public:
        OpenGlAttributes();
        virtual ~OpenGlAttributes();

        virtual HashType getName() { return AttributesGroup::OpenGl; };

        unsigned char& r() { return m_r; };
        unsigned char& g() { return m_g; };
        unsigned char& b() { return m_b; };
        const unsigned char& r() const { return m_r; };
        const unsigned char& g() const { return m_g; };
        const unsigned char& b() const { return m_b; };

        signed int& x() { return m_x; };
        signed int& y() { return m_y; };
        signed int& z() { return m_z; };
        const signed int& x() const { return m_x; };
        const signed int& y() const { return m_y; };
        const signed int& z() const { return m_z; };

    private:
        unsigned char m_r, m_g, m_b;
        signed int m_x, m_y, m_z;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<OpenGlAttributes, Attributes>(
                    static_cast<OpenGlAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes)
                   & BOOST_SERIALIZATION_NVP(m_r)
                   & BOOST_SERIALIZATION_NVP(m_g)
                   & BOOST_SERIALIZATION_NVP(m_b)
                   & BOOST_SERIALIZATION_NVP(m_x)
                   & BOOST_SERIALIZATION_NVP(m_y)
                   & BOOST_SERIALIZATION_NVP(m_z);
            };
    }; //OpenGlAttributes

}; //pann

#endif

