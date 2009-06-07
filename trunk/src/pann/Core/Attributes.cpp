//Attribute.cpp

#include "Includes/BoostCommon.h"

#include "Attributes.h"

using namespace std;

namespace pann
{
    HashType
    hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        //return hasher(_name);

        //Own realization. Returns small int

        typedef map<HashType, int> reg_t;
        static reg_t name_register;
        static int last = 1;

        HashType name = hasher(_name);

        reg_t::iterator it = name_register.find(name);
        if(name_register.end() == it)
        {
            name_register[name] = last;
            return last++;
        }

        return it->second;
    } //hash

    /*
    AttributeName
    hash(const char* _name, HashType _group)
    {
        AttributeName result = { hash(_name), _group };

        return result;
    } //hash

    bool operator<(const AttributeName& _lhs, const AttributeName& _rhs)
    {
        return (_lhs.name + _lhs.group < _rhs.name + _rhs.group);
    } //operator<
    */
}; //pann

