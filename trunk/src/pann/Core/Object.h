
#ifndef OBOJECT_H
#define OBOJECT_H

#include "Includes.h"

namespace pann
{
    class Object
    {
    public:
        Object();
        virtual ~Object();

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
            };
    };

}; //pann
#endif

