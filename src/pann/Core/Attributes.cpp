//Attributes.cpp

#include "Attributes.h"

namespace pann
{             
    AttributeNameHash
    hash(char* _name)
    {
        return boost::hash(_name);
    } //hash

    Attributes::Attributes()
    {                              
    } //Attributes                      

    Attributes::~Attributes()
    {                
    } //~Attributes      

    bool
    Attributes::is(const AttributeName _attributeName) const
    {                                             
        if (attributes.find(_attributeName) == attributes.end())
            return false;                           

        return true;
    } //is              

    void
    Attributes::unset(const AttributeName _attributeName)
    {                                          
        if(!attributes.erase(_attributeName))
            throw Exception::AttributesNotFound()<<"Attributes::unset(): attribute "<<_attributeName<<" not found\n";  
    } //unset                                  

    
    AttributeType&
    Attributes::operator[](const AttributeName _attributeName)
    {
        return attributes[_attributeName];
    } //operator[]
   
    void Attributes::erase()
    {
        attributes.clear();
    } //erase

}; //namespace pann

