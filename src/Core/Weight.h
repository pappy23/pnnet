/**
 * @file
 * Weight object
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Includes.h"
#include "Object.h"

namespace pann
{
    /**
     * Weight object, used in pann::Link. Weight might be shared among different Links.
     * Link contain boost::shared_ptr<Weight> for this object
     */
    class Weight : public Object
    {
        /* Public interface */
    public:
        Weight(Float _value = 1) : 
            value(_value),
            usageCount(1) { };
        ~Weight() { };

        /* Public members */
    public:
        Float value; ///< weight itself
        unsigned usageCount; ///< Used by weight update algorithms for shared weights

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            //ar & boost::serialization::base_object<Object>(*this);
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
             & BOOST_SERIALIZATION_NVP(usageCount)
             & BOOST_SERIALIZATION_NVP(value);
        };
    };

}; //pann

#endif //WEIGHT_H

