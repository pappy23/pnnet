//Object.cpp

#include "Object.h"

namespace pann
{             
    Object::Object()
    {                              
    } //Attributes                      

    Object::~Object()
    {                
    } //~Attributes      

    bool
    Object::is(const AttributeName _attributeName) const
    {                                             
        if(attributes.find(_attributeName) == attributes.end())
            return false;

        return true;
    } //is              

    void
    Object::unset(const AttributeName _attributeName)
    {                                          
        if(!attributes.erase(_attributeName))
            throw NotFound()<<"Attributes::unset(): attribute "<<_attributeName.name<<" not found\n";  
    } //unset                                  

    AttributeType&
    Object::at(const AttributeName _attributeName)
    {
        return attributes[_attributeName];
    } //at
   
    AttributeType&
    Object::operator[](const AttributeName _attributeName)
    {
        return at(_attributeName);
    } //operator[]
   
    const AttributeType&
    Object::at(const AttributeName _attributeName) const
    {
        std::map<AttributeName, AttributeType>::const_iterator iter = attributes.find(_attributeName);
        if(iter == attributes.end())
            throw NotFound()<<"Attributes::get(): attribute "<<_attributeName.name<<" not found\n";  
        
        return iter->second;
    } //at
   
    const AttributeType&
    Object::operator[](const AttributeName _attributeName) const
    {
        return at(_attributeName);
    } //operator[]

    void
    Object::erase()
    {
        attributes.clear();
    } //erase

    void
    Object::erase(HashType _groupName)
    {
        std::map<AttributeName, AttributeType>::iterator iter = attributes.begin();
        for(; iter != attributes.end(); ++iter)
            if(iter->first.group == _groupName)
                attributes.erase(iter);
    } //eraseGroup

}; //namespace pann

