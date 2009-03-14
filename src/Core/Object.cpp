/**
 * @file
 * Object realization
 */

#include "Object.h"

using std::map;
using std::string;
using boost::any;

namespace pann
{             
    Object::Object(UINT _id)
    {                              
        id = _id;
    } //Object                      

    /*virtual*/
    Object::~Object()
    {                
    } //~Object      

    UINT
    Object::getId()
    {
        return id;
    }

    bool
    Object::is(const string& _attributeName) const
    {                                             
        if (attributes.find(_attributeName) == attributes.end())
            return false;                           

        return true;
    } //is              

    void
    Object::unset(const string& _attributeName)
    {                                          
        if(!attributes.erase(_attributeName))
			; // TODO: Check this
            //throw Exception::ObjectNotFound()<<"Object::unset(): attribute "<<_attributeName<<" not found\n";  
    } //unset                                  

    
    any &
    Object::operator[](const string& _attributeName)
    {
        return attributes[_attributeName];
    } //operator[]
   
    void Object::erase()
    {
        attributes.clear();
    } //erase

}; //namespace NNet

