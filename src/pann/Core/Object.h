#ifndef OBJECT_H
#define OBJECT_H

#include "Includes/Std.h"
#include "Includes/BoostSerialization.h"

#include "Exception.h"
#include "Attributes.h"

//TODO present attrbutes group realisation
//TODO is somewhat drafty

namespace pann
{
    class Object
    {
    public:
        Object() : attributes(10, AttributesPtr((Attributes*)0)) { };
        virtual ~Object() { };

        /**
         * Get reference to attributes group. Create it if needed
         * @param _groupName - group name
         * @return - reference to attributes group
         */
        template<class T>
        boost::shared_ptr<T> at(const HashType _groupName) const
        {
            return boost::static_pointer_cast<T, Attributes>(attributes[_groupName]);
        };

        template<class T>
        boost::shared_ptr<T> operator[](const HashType _groupName) const
        {
            return at<T>(_groupName);
        };

    private:
        std::vector<AttributesPtr> attributes;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(attributes);
            };
    };

}; //pann

#endif

