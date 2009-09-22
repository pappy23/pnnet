/**
 * @file
 * Weight object
 */

#ifndef WEIGHT_H
#define WEIGHT_H

#include <boost/thread/mutex.hpp>

#include "Includes/BoostSerialization.h"

#include "Type.h"
#include "Object.h"

namespace pann
{
    /**
     * Weight object, used in pann::Link. Weight might be shared among different Links.
     * Link contains WeightPtr for this object
     */
    class Weight : public Object
    {
    public:
        Weight(Float _value = 1);
        virtual ~Weight();

        Float getValue() const;
        void setValue(Float _value);

        /**
         * Add _delta / ( usageCount / 2 ) to value
         */
        Float addValue(Float _delta);

        /**
         * Every time Link object with current Weight is created,
         * it increments usageCount counter
         * It is used later in learning algorithms for shared weights
         */
        unsigned getUsageCount() const;
        unsigned incUsageCount();
        unsigned decUsageCount();

        /**
         * Restrict Weight modifications by concurrent threads
         * boost::mutex is used
         * Use case: boost::mutex::scoped_lock lock( w.getMutex() )
         */
        boost::mutex& getMutex();

    private:
        Float value;
        unsigned usageCount; ///< Used by weight update algorithms for shared weights
        boost::mutex mutex;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(value)
               & BOOST_SERIALIZATION_NVP(usageCount);
        };
    };

}; //pann

#endif //WEIGHT_H

