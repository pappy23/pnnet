//Object.cpp

#include "Object.h"

namespace pann
{             
    Object::Object() throw()
    {                              
        attributes = 0;
    } //Attributes                      

    Object::~Object() throw()
    {                
        if(attributes)
            delete attributes;
    } //~Attributes      

    bool
    Object::is(const AttributeName _attributeName) const throw()
    {                                             
        if(!attributes)
            return false;                           
        
        if(attributes->find(_attributeName) == attributes->end())
            return false;

        return true;
    } //is              

    void
    Object::unset(const AttributeName _attributeName) throw(E<Exception::ObjectNotFound>)
    {                                          
        if(!attributes || !attributes->erase(_attributeName))
            throw E<Exception::ObjectNotFound>()<<"Attributes::unset(): attribute "<<_attributeName.name<<" not found\n";  
    } //unset                                  

    
    AttributeType&
    Object::operator[](const AttributeName _attributeName) throw()
    {
        if(!attributes)
            attributes = new std::map<AttributeName, AttributeType>();

        return (*attributes)[_attributeName];
    } //operator[]
   
    const AttributeType&
    Object::operator[](const AttributeName _attributeName) const throw(E<Exception::ObjectNotFound>)
    {
        if(!attributes)
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName.name<<" not found\n";  

        std::map<AttributeName, AttributeType>::const_iterator iter = attributes->find(_attributeName);
        if(iter == attributes->end())
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName.name<<" not found\n";  
        
        return iter->second;
    } //get

    void
    Object::erase() throw()
    {
        if(attributes)
            delete attributes;
    } //erase

    void
    Object::erase(HashType _groupName) throw()
    {
        if(!attributes)
            return;

        std::map<AttributeName, AttributeType>::iterator iter = attributes->begin();
        for(; iter != attributes->end(); ++iter)
            if(iter->first.group == _groupName)
                attributes->erase(iter);
    } //eraseGroup

}; //namespace pann

