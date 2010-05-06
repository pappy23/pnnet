//Object.cpp

namespace pann
{
    Float
    Object::get_attr(Hash key) const
    {
        std::map<Hash, Float>::const_iterator it = m_attribute_map.find(key);
        if(it == m_attribute_map.end())
            throw NotFound()<<"Attribute "<<key<<" not found\n";

        return *it;
    }; //get_attr
}; //pann
