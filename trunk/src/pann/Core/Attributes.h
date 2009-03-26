#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"
#include "Object.h"

namespace pann
{
    typedef std::size_t AttributeNameHash;
    typedef Float AttributeType;

    AttributeNameHash hash(const char* _name);

    class Attributes : public Object
    {
    protected:
        //TODO Replace map<> with map<> and reimplement public methods so
        //they check wether map<> is NULL. It can decrease memory usage when
        //attributes not in use and simplify using of Attributes object,
        //hiding pointer details
        std::map<AttributeNameHash, AttributeType> attributes;

    public:
        Attributes() throw();
        virtual ~Attributes() throw();

        //! Does attribute exist?
        //! @param _attributeName - checking attribute name
        bool is(const AttributeNameHash _attributeName) const throw();

        //! Delete attribute
        //! @param _attributeName - deleting attribute name
        void unset(const AttributeNameHash _attributeName) throw(Exception::ObjectNotFound);

        //! Get reference to attribute. Create it if nonexistent
        //! @param _attributeName - getting attribute name
        //! @return - reference to attribute
        AttributeType& operator[](const AttributeNameHash _attributeName) throw();

        /**
         * Get attribute. Nonintrusive version of operator[]
         */
        const AttributeType& operator[](const AttributeNameHash _attributeName) const throw(Exception::ObjectNotFound);

        //! Delete all attributes
        void erase() throw();

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                   & BOOST_SERIALIZATION_NVP(attributes);
            };
    };

}; //pann

#endif

