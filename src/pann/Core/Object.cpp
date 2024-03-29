//Object.cpp

#include "Object.h"
#include "Exception.h"

namespace pann
{
    bool
    Object::is_attr(Hash key) const
    {
        return (m_attribute_map.find(key) != m_attribute_map.end());
    }; //is_attr

    Float
    Object::get_attr(Hash key) const
    {
        std::map<Hash, Float>::const_iterator it = m_attribute_map.find(key);
        if(it == m_attribute_map.end())
            throw NotFound()<<"Attribute "<<key<<" not found\n";

        return it->second;
    }; //get_attr

    Float&
    Object::get_attr_ref(Hash key)
    {
        return m_attribute_map[key];
    }; //get_attr_ref

    void
    Object::set_attr(Hash key, Float value)
    {
        m_attribute_map[key] = value;
    }; //set_attr
}; //pann

