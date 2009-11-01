/**
 * @file
 * Weight object
 */

#ifndef PANN_CORE_WEIGHT_H_INCLUDED
#define PANN_CORE_WEIGHT_H_INCLUDED

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
        explicit Weight(Float value = 1): value_(value), usage_(0) {};
        //TODO: Noncopiable
        virtual ~Weight() {};

        operator Float() const
        {
            return value_;
        };

        /**
         * Add delta / ( usage_ / 2 ) to value_
         */
        operator+=(Float delta)
        {
            boost::mutex::scoped_lock lock(mutex_);

            return m_value += _delta * 2.0 / Float(m_usageCount);
        }

        /**
         * Every time Link object with current Weight is created,
         * it increments usageCount counter
         * It is used later in learning algorithms for shared weights
         */
        unsigned get_usage() const
        {
            return usage_;
        }

        void inc_usage()
        {
            ++usage_;
        }

        void dec_usage()
        {
            if(usage_ == 0)
                throw Exception()<<"Negative usage count\n";

            --usage_;
        }

    private:
        Float value_;
        unsigned usage_; ///< Used by weight update algorithms for shared weights
        boost::mutex mutex_;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(value_)
               & BOOST_SERIALIZATION_NVP(usage_);
        };
    };
    ADD_PTR_TYPEDEF(Weight);

}; //pann

DEFINE_PYTHON_EXPORT(Weight);

