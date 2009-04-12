#ifndef OBJECT_H
#define OBJECT_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"
#include "Attribute.h"

namespace pann
{
    class Object
    {
    public:
        Object() throw();
        virtual ~Object() throw();

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
        void erase(HashType _groupName) throw();

    private:
        std::map<AttributeName, AttributeType>* attributes;

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

