/**
 * @file
 * Weight object
 */

#ifndef PANN_CORE_WEIGHT_H_INCLUDED
#define PANN_CORE_WEIGHT_H_INCLUDED

#include <boost/thread/mutex.hpp>

#include "Includes/BoostSerialization.h"

#include "Type.h"
//#include "Object.h"

namespace pann
{
    /**
     * Weight object, used in pann::Link. Weight might be shared among different Links.
     * Link contains WeightPtr for this object
     */
    class Weight //: public Object
    {
    public:
        Weight(Float _value = 1): m_value(_value), m_usageCount(0) {};
        virtual ~Weight() {};

        Float getValue() const { return m_value; };

        /**
         * Add _delta / ( usageCount / 2 ) to value
         */
        Float addValue(Float _delta)
        {
            boost::mutex::scoped_lock lock(m_mutex);
            return m_value += _delta * 2.0 / Float(m_usageCount);
        }

        /**
         * Every time Link object with current Weight is created,
         * it increments usageCount counter
         * It is used later in learning algorithms for shared weights
         */
        unsigned getUsageCount() const { return m_usageCount; };

        unsigned incUsageCount()
        {
            return ++m_usageCount;
        }

        unsigned decUsageCount()
        {
            if(m_usageCount == 0)
                throw Exception()<<"Weight::decUsageCount(): negative usage count\n";

            return --m_usageCount;
        }

    private:
        Float m_value;
        unsigned m_usageCount; ///< Used by weight update algorithms for shared weights
        boost::mutex m_mutex;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar //& BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(m_value)
               & BOOST_SERIALIZATION_NVP(m_usageCount);
        };
    };
    ADD_PTR_TYPEDEF(Weight);

}; //pann

#endif //PANN_CORE_WEIGHT_H_INCLUDED

