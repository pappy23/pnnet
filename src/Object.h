/**
 * @file
 * Basic Object, equiped with random acess attributes of boost::any
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"

namespace pann
{
    //! Base class for almoust everything
    class Object
    {
    public:
        Object();
        virtual ~Object();

        //! Does attribute @param exist?
        bool is(const std::string&) const;

        //! Delete attribute
        void unset(const std::string&);
        
        //! Get reference to attribute. Create it if nonexistent
        boost::any& operator[](const std::string&);

        //! Delete all attributes
        void erase();

        virtual void printDebugInfo(std::ostringstream& ost) = 0;

    protected:
        mutable std::map<std::string, boost::any> attributes;
    };

}; //pann

#endif
