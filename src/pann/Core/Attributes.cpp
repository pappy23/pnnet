//Attributes.cpp

#include "Attributes.h"

REGISTER_ATTRIBUTES_CPP(OpenGlAttributes);

namespace pann
{
    HashType
    hash(const char* _name)
    {
        static boost::hash<std::string> hasher;
        return hasher(_name);
    }; //hash

}; //pann

