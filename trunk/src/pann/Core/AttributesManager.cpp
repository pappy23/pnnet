//AttributesManager.cpp

#include "AttributesManager.h"

namespace pann
{             
    AttributesManager::AttributesManager(Object* first, ...)
    {
        Object* current = first;
        va_list vl;
        va_start(vl, first);

        do {
            chain.push_back(current);
            current = va_arg(vl, Object*);
        } while(current != 0);

    } //AttributesManager

    AttributesManager::~AttributesManager()
    {
    } //~AttributesManager

    bool
    AttributesManager::is(const AttributeNameHash _attributeName) const throw()
    {
        BOOST_FOREACH( const Object* obj, chain )
            if(obj->attr.is(_attributeName))
                return true;

        return false;
    } //is

    void
    AttributesManager::unset(const AttributeNameHash _attributeName) throw(E<Exception::ObjectNotFound>)
    {
        //TODO: may be i should add _recursive parametr?
        chain.front()->attr.unset(_attributeName);
    } //unset

    AttributeType&
    AttributesManager::operator[](const AttributeNameHash _attributeName) throw()
    {
        return chain.front()->attr[_attributeName];
    } //operator[]

    const AttributeType&
    AttributesManager::operator[](const AttributeNameHash _attributeName) const throw(E<Exception::ObjectNotFound>)
    {
        BOOST_FOREACH( const Object* obj, chain )
            if(obj->attr.is(_attributeName))
                return obj->attr[_attributeName];

        throw E<Exception::ObjectNotFound>;

        //return chain.first()->attr[_attributeName]; //shut up, gcc!
    } //operator[]

}; //namespace pann

