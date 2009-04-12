//AttributesManager.cpp

#include "AttributesManager.h"

namespace pann
{             
    AttributesManager::AttributesManager(Object* first, ...) throw()
    {
        Object* current = first;
        va_list vl;
        va_start(vl, first);

        do {
            chain.push_back(current);
            current = va_arg(vl, Object*);
        } while(current != 0);

        va_end(vl);

        std::cout<<chain.size()<<std::endl;

    } //AttributesManager

    AttributesManager::~AttributesManager() throw()
    {
    } //~AttributesManager

    bool
    AttributesManager::is(const AttributeName _attributeName) const throw()
    {
        BOOST_FOREACH( const Object* obj, chain )
            if(obj->attr.is(_attributeName))
                return true;

        return false;
    } //is

    void
    AttributesManager::unset(const AttributeName _attributeName) throw(E<Exception::ObjectNotFound>)
    {
        //TODO: may be i should add _recursive parametr?
        chain.front()->attr.unset(_attributeName);
    } //unset

    AttributeType&
    AttributesManager::operator[](const AttributeName _attributeName) throw()
    {
        return chain.front()->attr[_attributeName];
    } //operator[]

    const AttributeType&
    AttributesManager::operator[](const AttributeName _attributeName) const throw(E<Exception::ObjectNotFound>)
    {
        BOOST_FOREACH( const Object* obj, chain )
            if(obj->attr.is(_attributeName))
                return obj->attr[_attributeName];

        throw E<Exception::ObjectNotFound>()<<"AttributesManager::operator[]: Can't find attribute "<<_attributeName.name<<"\n";

        //return chain.first()->attr[_attributeName]; //shut up, gcc!
    } //operator[]

    void
    AttributesManager::erase(AttributeHash _groupName) throw()
    {
        chain.front()->attr.erase(_groupName);
    } //eraseGroup

}; //namespace pann

