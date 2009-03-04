//Object.cpp                                                                                                   

#include "Object.h"

using std::ostringstream;
using std::endl;         
using std::string;       
using std::map;          
using std::setprecision; 

namespace NNet
{             
        Object::Object(Object* pParent)
        {                              
                this->pParent = pParent;
        } //Object                      

        /*virtual*/
        Object::~Object()
        {                
        } //~Object      

        void
        Object::setParent(Object* pParent)
        {                                 
                this->pParent = pParent;  
        } //setParent                     

        Object*
        Object::getParent()
        {                  
                return this->pParent;
        } //getParent                

        bool
        Object::is(const string& rAttributeName) const
        {                                             
                if (Attributes.find(rAttributeName) == Attributes.end())
                {                                                       
                        if (!pParent || !pParent->is(rAttributeName))   
                        {                                               
                                return false;                           
                        }                                               
                }                                                       

                return true;
        } //is              

        void
        Object::unset(const string& rAttributeName)
        {                                          
                Attributes.erase(rAttributeName);  
        } //unset                                  

        void
        Object::set(const string& rAttributeName, tAttribute AttributeValue)
        {                                                                   
                if (pParent &&                                              
                        pParent->is(rAttributeName) &&                      
                        pParent->get(rAttributeName) == AttributeValue)     
                {                                                           
                        Attributes.erase(rAttributeName);                   
                        return;                                             
                }                                                           

                Attributes[rAttributeName] = AttributeValue;
        } //set                                             

        void
        Object::set(const string& rAttributeName, tFloat AttributeValue)
        {                                                               
        tAttribute newAttribute;                                        
        newAttribute.setType(tAttribute::AttributeTypeFloat);           
        newAttribute.Value.Float = AttributeValue;                      
                                                                        
        set(rAttributeName, newAttribute);                              
        } //set                                                         

        void
        Object::set(const string& rAttributeName, const std::string& AttributeValue)
        {                                                                           
        tAttribute newAttribute;                                                    
        newAttribute.setType(tAttribute::AttributeTypeString);                      
        *(newAttribute.Value.pString) = AttributeValue;                             
                                                                                    
        set(rAttributeName, newAttribute);                                          
        } //set                                                                     

    void
    Object::setAttribute(const std::string& rAttributeName, tAttribute AttributeValue)
    {                                                                                 
        this->set(rAttributeName, AttributeValue);                                    
    } //setAttribute                                                                  

    void
    Object::setFloat(const std::string& rAttributeName, tFloat AttributeValue)
    {                                                                         
        this->set(rAttributeName, AttributeValue);                            
    } //setFloat                                                              

    void
    Object::setString(const std::string& rAttributeName, const string& AttributeValue)
    {                                                                                 
        this->set(rAttributeName, AttributeValue);                                    
    } //setString                                                                     

        tAttribute
        Object::get(const string& rAttributeName) const
        {                                              
                if (Attributes.find(rAttributeName) == Attributes.end())
                {                                                       
                        if (pParent && pParent->is(rAttributeName))     
                        {                                               
                                return pParent->get(rAttributeName);    
                        }                                               
                        else                                            
                        {                                               
                                throw Exception("Requested get() of unknown attribute %s", rAttributeName.c_str());
                        }                                                                                          
                }                                                                                                  

                return Attributes[rAttributeName];
        } //get                                   

    tAttribute
    Object::getAttribute(const string& rAttributeName) const
    {                                                       
        return get(rAttributeName);                         
    } //getAttribute                                        

    tFloat
    Object::getFloat(const string& rAttributeName) const
    {
        tAttribute attr = get(rAttributeName);
        if(attr.getType() != tAttribute::AttributeTypeFloat)
            throw Exception("Requested getFloat() of attribute %s, but it's type isn't tFloat");

        return attr.Value.Float;
    } //getFloat

    const string&
    Object::getString(const string& rAttributeName) const
    {
        tAttribute attr = get(rAttributeName);
        if(attr.getType() != tAttribute::AttributeTypeString)
            throw Exception("Requested getString() of attribute %s, but it's type isn't tString");

        return *attr.Value.pString;
    } //getString

    tAttribute
    Object::operator[](const string& rAttributeName) const
    {
                return get(rAttributeName);
    } //operator[]

        const string
        Object::stat() const
        {
                ostringstream ost;
                map<string, tAttribute>::const_iterator i = Attributes.begin();
                for (; i != Attributes.end(); i++)
                {
            ost<<" "<<i->first<<" = "<<i->second.getType()<<":"<<i->second.toString()<<endl;
                }

                return ost.str();
        } //stat

}; //namespace NNet

