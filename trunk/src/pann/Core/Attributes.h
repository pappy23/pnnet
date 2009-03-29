#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"
#include "Object.h"

namespace pann
{
    //TODO test performance and memory usage when using string or size_t as attribute key
    typedef std::string AttributeNameHash;
    //typedef std::size_t AttributeNameHash;
    typedef Float AttributeType;

    AttributeNameHash hash(const char* _name) throw();

    class Attributes : public Object
    {
    protected:
        std::map<AttributeNameHash, AttributeType>* attributes;

    public:
        Attributes() throw();
        virtual ~Attributes() throw();

        //! Does attribute exist?
        //! @param _attributeName - checking attribute name
        bool is(const AttributeNameHash _attributeName) const throw();

        //! Delete attribute
        //! @param _attributeName - deleting attribute name
        void unset(const AttributeNameHash _attributeName) throw(E<Exception::ObjectNotFound>);

        //! Get reference to attribute. Create it if nonexistent
        //! @param _attributeName - getting attribute name
        //! @return - reference to attribute
        AttributeType& operator[](const AttributeNameHash _attributeName) throw();

        /**
         * Get attribute. Nonintrusive version of operator[]
         */
        const AttributeType& operator[](const AttributeNameHash _attributeName) const throw(E<Exception::ObjectNotFound>);

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

