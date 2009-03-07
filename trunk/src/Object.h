//Object.h                                                                                                                    
#ifndef OBJECT_H
#define OBJECT_H

#include "Includes.h"
#include "Exception.h"

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
        mutable std::map<std::string, boost::any> attributes;
    };

}; //namespace NNet

#endif
