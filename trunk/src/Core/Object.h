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
    protected:
        mutable std::map<std::string, boost::any> attributes; //!< left -  name, right - parametr
        UINT id;

    public:
        Object(UINT _id = 0);
        virtual ~Object();
        
        virtual UINT getId();

        //! Does attribute exist?
        //! @param _attributeName - checking attribute name
        bool is(const std::string& _attributeName) const;

        //! Delete attribute
        //! @param _attributeName - deleting attribute name
        void unset(const std::string& _attributeName);

        //! Get reference to attribute. Create it if nonexistent
        //! @param _attributeName - getting attribute name
        //! @return - reference to attribute
        boost::any& operator[](const std::string& _attributeName);

        //! Delete all attributes
        void erase();

    public:
        virtual void printDebugInfo(std::ostringstream& ost) = 0;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                //ar & attributes;
            };
    };

}; //pann

#endif
