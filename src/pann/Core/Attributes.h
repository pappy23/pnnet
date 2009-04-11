#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"

namespace pann
{
    //typedef std::string AttributeHash;
    typedef std::size_t AttributeHash;

    AttributeHash hash(const char* _name) throw();

    typedef struct {
        AttributeHash name;
        AttributeHash group;
        //AttributeFlags flags; //scope, inheritance, other properties

        /* Serialization */
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 ar & BOOST_SERIALIZATION_NVP(name)
                    & BOOST_SERIALIZATION_NVP(group);
            };
    } AttributeName;

    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs);

    typedef Float AttributeType;

    class Attributes
    {
    protected:
        std::map<AttributeName, AttributeType>* attributes;

    public:
        Attributes() throw();
        virtual ~Attributes() throw();

        //! Does attribute exist?
        //! @param _attributeName - checking attribute name
        bool is(const AttributeName _attributeName) const throw();

        //! Delete attribute
        //! @param _attributeName - deleting attribute name
        void unset(const AttributeName _attributeName) throw(E<Exception::ObjectNotFound>);

        //! Get reference to attribute. Create it if nonexistent
        //! @param _attributeName - getting attribute name
        //! @return - reference to attribute
        AttributeType& operator[](const AttributeName _attributeName) throw();

        /**
         * Get attribute. Nonintrusive version of operator[]
         */
        const AttributeType& operator[](const AttributeName _attributeName) const throw(E<Exception::ObjectNotFound>);

        //! Delete all attributes
        void erase() throw();

        //! Delete only attributes from specific group
        void erase(AttributeHash _groupName) throw();

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(attributes);
            };
    };

}; //pann

#endif

