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
    Object::Object()
    {                              
    } //Object                      

    /*virtual*/
    Object::~Object()
    {                
    } //~Object      

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
            throw Exception::ObjectNotFound()<<"Object::unset(): attribute "<<_attributeName<<" not found\n";  
    } //unset                                  

    any &
    Object::operator[](const string& _attributeName)
    {
        return attributes[_attributeName];
    } //operator[]

}; //namespace NNet

