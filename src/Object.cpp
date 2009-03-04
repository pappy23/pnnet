//Object.cpp                                                                                                   

#include "Object.h"

using std::map;
using std::string;
using boost::any;

namespace pann
{             
    Object::Object(int id) : obj_id(id)
    {                              
    } //Object                      

    /*virtual*/
    Object::~Object()
    {                
    } //~Object      

    int
    Object::id()
    {
        return this->obj_id;
    } //id

    bool
    Object::is(const string& rAttributeName) const
    {                                             
        if (Attributes.find(rAttributeName) == Attributes.end())
            return false;                           

        return true;
    } //is              

    void
    Object::unset(const string& rAttributeName)
    {                                          
        Attributes.erase(rAttributeName);  
    } //unset                                  

    any &
    Object::operator[](const string& rAttributeName)
    {
        return Attributes[rAttributeName];
    } //operator[]

}; //namespace NNet

