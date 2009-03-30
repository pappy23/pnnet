/**
 * @file
 * Weight object
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Includes.h"
#include "Type.h"
#include "Object.h"
#include "Attributes.h"

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
        Weight(Float _value = 1) throw();
        virtual ~Weight() throw();

        /* Public members */
    public:
        Float value; ///< weight itself
        unsigned usageCount; ///< Used by weight update algorithms for shared weights
        Attributes learningHint;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
             & BOOST_SERIALIZATION_NVP(usageCount)
             & BOOST_SERIALIZATION_NVP(value)
             & BOOST_SERIALIZATION_NVP(learningHint);
        };
    };

}; //pann

#endif //WEIGHT_H

