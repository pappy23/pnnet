/**
 * @file
 * This file defines some attribute related staff and
 * declares common attributes groups and names
 * UPDATE: File contains only abstract interface declaration
 *
 * README:
 * Every class derived from Object (@see Object.h)
 * has ability to use attributes
 * Object contains map<HashType, AttributesPtr>
 */
#ifndef PANN_CORE_ATTRIBUTES_H_INCLUDED
#define PANN_CORE_ATTRIBUTES_H_INCLUDED

#include "Includes/BoostSerialization.h"
#include "Type.h"

namespace pann
{
    /**
     * Base class without instances
     */
    class Attributes
    {
    public:
        virtual ~Attributes() {};

    protected:
        Attributes() {};

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                //empty
            };
    }; //Attributes
    ADD_PTR_TYPEDEF(Attributes);

}; //pann

#endif //PANN_CORE_ATTRIBUTES_H_INCLUDED

