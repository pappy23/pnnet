//Attributes.cpp

#include "Attributes.h"

namespace pann
{             
    AttributeHash
    hash(const char* _name) throw()
    {
        //return std::string(_name);
        static boost::hash<std::string> hasher;
        return hasher(_name);
    } //hash

    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs)
    {
        //return (_lhs.name + _lhs.group < _rhs.name + _rhs.group);
        return _lhs.name < _rhs.name;
    };
        
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
    Attributes::is(const AttributeName _attributeName) const throw()
    {                                             
        if(!attributes)
            return false;                           
        
        if(attributes->find(_attributeName) == attributes->end())
            return false;

        return true;
    } //is              

    void
    Attributes::unset(const AttributeName _attributeName) throw(E<Exception::ObjectNotFound>)
    {                                          
        if(!attributes || !attributes->erase(_attributeName))
            throw E<Exception::ObjectNotFound>()<<"Attributes::unset(): attribute "<<_attributeName.name<<" not found\n";  
    } //unset                                  

    
    AttributeType&
    Attributes::operator[](const AttributeName _attributeName) throw()
    {
        if(!attributes)
            attributes = new std::map<AttributeName, AttributeType>();

        return (*attributes)[_attributeName];
    } //operator[]
   
    const AttributeType&
    Attributes::operator[](const AttributeName _attributeName) const throw(E<Exception::ObjectNotFound>)
    {
        if(!attributes)
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName.name<<" not found\n";  

        std::map<AttributeName, AttributeType>::const_iterator iter = attributes->find(_attributeName);
        if(iter == attributes->end())
            throw E<Exception::ObjectNotFound>()<<"Attributes::get(): attribute "<<_attributeName.name<<" not found\n";  
        
        return iter->second;
    } //get

    void Attributes::erase() throw()
    {
        delete attributes;
    } //erase

    void Attributes::erase(AttributeHash _groupName) throw()
    {
        std::map<AttributeName, AttributeType>::iterator iter = attributes->begin();
        for(; iter != attributes->end(); ++iter)
            if(iter->first.group == _groupName)
                attributes->erase(iter);
    } //eraseGroup

}; //namespace pann

