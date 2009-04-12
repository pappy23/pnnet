//Object.cpp

#include "Object.h"

namespace pann
{             
    HashType
    hash(const char* _name) throw()
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    } //hash

    AttributeName
    hash(const char* _name, const char* _group) throw()
    {
        AttributeName result = { hash(_name), hash(_group) };

        return result;
    } //hash

    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs) throw()
    {
        return (_lhs.name + _lhs.group < _rhs.name + _rhs.group);
    } //operator<
        
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
        delete attributes;
    } //erase

    void
    Object::erase(HashType _groupName) throw()
    {
        std::map<AttributeName, AttributeType>::iterator iter = attributes->begin();
        for(; iter != attributes->end(); ++iter)
            if(iter->first.group == _groupName)
                attributes->erase(iter);
    } //eraseGroup

}; //namespace pann

