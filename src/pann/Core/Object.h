
#ifndef OBOJECT_H
#define OBOJECT_H

#include "Includes.h"
#include "Attributes.h"

namespace pann
{
    class AttributesManager;

    class Object
    {
    public:
        Object();
        virtual ~Object();

        /* Attributes */
    private:
        friend class AttributesManager;
        Attributes attr;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 ar & BOOST_SERIALIZATION_NVP(attr);
            };
    };

}; //pann
#endif

