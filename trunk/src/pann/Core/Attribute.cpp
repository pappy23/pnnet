//Attribute.cpp

#include "Attribute.h"

namespace pann
{
    HashType
    hash(const char* _name) throw()
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    } //hash

    AttributeName
    hash(const char* _name, HashType _group) throw()
    {
        AttributeName result = { hash(_name), _group };

        return result;
    } //hash

    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs) throw()
    {
        return (_lhs.name + _lhs.group < _rhs.name + _rhs.group);
    } //operator<

}; //pann

