#ifndef ATTRIBUTESMANAGER_H
#define ATTRIBUTESMANAGER_H

#include "Includes.h"
#include "Object.h"

namespace pann
{
    class AttributesManager
    {
    public:
        AttributesManager(Object*, ...) throw();
        ~AttributesManager() throw();

        bool is(const AttributeNameHash _attributeName) const throw();
        void unset(const AttributeNameHash _attributeName) throw(E<Exception::ObjectNotFound>);
        AttributeType& operator[](const AttributeNameHash _attributeName) throw();
        const AttributeType& operator[](const AttributeNameHash _attributeName) const throw(E<Exception::ObjectNotFound>);

    private:
        std::list<Object*> chain;
    };

}; //pann

#endif

