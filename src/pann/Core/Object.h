#ifndef OBJECT_H
#define OBJECT_H

#include "Includes/Std.h"
#include "Includes/BoostSerialization.h"

#include "Exception.h"
#include "Attribute.h"

namespace pann
{
    class Object
    {
    public:
        Object() {};
        virtual ~Object() {};

        /**
         * Does attribute exist?
         * @param _attributeName - checking attribute name
         */
//        bool is(const AttributeName _attributeName) const;

        /**
         * Delete attribute
         * @param _attributeName - deleting attribute name
         */
//        void unset(const AttributeName _attributeName);

        /**
         * Get reference to attribute. Create it if nonexistent
         * @param _attributeName - getting attribute name
         * @return - reference to attribute
         */
//        AttributeType& at(const AttributeName _attributeName);
//        AttributeType& operator[](const AttributeName _attributeName);

        /**
         * Get attribute. Nonintrusive version of operator[]
         */
//        const AttributeType& at(const AttributeName _attributeName) const;
//        const AttributeType& operator[](const AttributeName _attributeName) const;

        /**
         * Delete all attributes
         */
//        void erase();

        /**
         * Delete only attributes from specific group
         */
//        void erase(HashType _groupName);

    private:
//        std::map<AttributeName, AttributeType> attributes;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
//                ar & BOOST_SERIALIZATION_NVP(attributes);
            };
    };

}; //pann

#endif

