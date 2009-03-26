//Attributes.cpp

#include "Attributes.h"

namespace pann
{             
    AttributeNameHash
    hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    } //hash

    Attributes::Attributes() throw()
    {                              
    } //Attributes                      

    Attributes::~Attributes() throw()
    {                
    } //~Attributes      

    bool
    Attributes::is(const AttributeNameHash _attributeName) const throw()
    {                                             
        if (attributes.find(_attributeName) == attributes.end())
            return false;                           

        return true;
    } //is              

    void
    Attributes::unset(const AttributeNameHash _attributeName) throw(Exception::ObjectNotFound)
    {                                          
        if(!attributes.erase(_attributeName))
            throw Exception::ObjectNotFound()<<"Attributes::unset(): attribute "<<_attributeName<<" not found\n";  
    } //unset                                  

    
    AttributeType&
    Attributes::operator[](const AttributeNameHash _attributeName) throw()
    {
        return attributes[_attributeName];
    } //operator[]
   
    const AttributeType&
    Attributes::operator[](const AttributeNameHash _attributeName) const throw(Exception::ObjectNotFound)
    {
        std::map<AttributeNameHash, AttributeType>::const_iterator iter = attributes.find(_attributeName);
        if(iter == attributes.end())
            throw Exception::ObjectNotFound()<<"Attributes::get(): attribute "<<_attributeName<<" not found\n";  
        
        return iter->second;
    } //get

    void Attributes::erase() throw()
    {
        attributes.clear();
    } //erase

}; //namespace pann

