//Attributes.cpp

#include "Attributes.h"

namespace pann
{             
    AttributeNameHash
    hash(const char* _name) throw()
    {
        return std::string(_name);

        //See Attributes.h TODO
        //static boost::hash<std::string> hasher;
        //return hasher(_name);
    } //hash

    Attributes::Attributes() throw()
    {                              
        attributes = 0;
    } //Attributes                      

    Attributes::~Attributes() throw()
    {                
        if(attributes)
            delete attributes;
    } //~Attributes      

    bool
    Attributes::is(const AttributeNameHash _attributeName) const throw()
    {                                             
        if (!attributes || attributes->find(_attributeName) == attributes->end())
            return false;                           

        return true;
    } //is              

    void
    Attributes::unset(const AttributeNameHash _attributeName) throw(E<Exception::ObjectNotFound>)
    {                                          
        if(!attributes || !attributes->erase(_attributeName))
            throw E<Exception::ObjectNotFound>()<<"Attributes::unset(): attribute "<<_attributeName<<" not found\n";  
    } //unset                                  

    
    AttributeType&
    Attributes::operator[](const AttributeNameHash _attributeName) throw()
    {
        if(!attributes)
            attributes = new std::map<AttributeNameHash, AttributeType>();

        return (*attributes)[_attributeName];
    } //operator[]
   
    const AttributeType&
    Attributes::operator[](const AttributeNameHash _attributeName) const throw(E<Exception::ObjectNotFound>)
    {
        if(!attributes)
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName<<" not found\n";  

        std::map<AttributeNameHash, AttributeType>::const_iterator iter = attributes->find(_attributeName);
        if(iter == attributes->end())
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName<<" not found\n";  
        
        return iter->second;
    } //get

    void Attributes::erase() throw()
    {
        delete attributes;
    } //erase

}; //namespace pann

