//Object.h                                                                                                                    
#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <string>

#include <boost/any.hpp>

namespace pann
{
    class Object
    {
    public:
        Object();
        virtual ~Object();

        bool is(const std::string&) const;
        void unset(const std::string&);
        boost::any& operator[](const std::string&);

    protected:
        mutable std::map<std::string, boost::any> Attributes;
    };

}; //namespace NNet

#endif
