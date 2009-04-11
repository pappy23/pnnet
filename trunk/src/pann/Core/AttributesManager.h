#ifndef ATTRIBUTESMANAGER_H
#define ATTRIBUTESMANAGER_H

#include "Includes.h"
#include "Object.h"
#include "Attributes.h"

namespace pann
{
    class AttributesManager
    {
    public:
        AttributesManager(Object*, ...) throw();
        ~AttributesManager() throw();

        bool is(const AttributeName _attributeName) const throw();
        void unset(const AttributeName _attributeName) throw(E<Exception::ObjectNotFound>);
        AttributeType& operator[](const AttributeName _attributeName) throw();
        const AttributeType& operator[](const AttributeName _attributeName) const throw(E<Exception::ObjectNotFound>);

        void erase(AttributeHash _groupName) throw();

    private:
        std::list<Object*> chain;
    };

}; //pann

#endif

