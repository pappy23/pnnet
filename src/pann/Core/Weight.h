/**
 * @file
 * Weight object
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Type.h"
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
        Weight(Float _value = 1, unsigned _usageCount = 1) throw();
        virtual ~Weight() throw();

        /* Attributes */
    public:
        static const AttributeName value; ///< weight itself

        /* Public members */
    public:
        boost::mutex mutex;
        //TODO: make it private. User is idiot
        unsigned usageCount; ///< Used by weight update algorithms for shared weights

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(usageCount);
        };
    };

}; //pann

#endif //WEIGHT_H

