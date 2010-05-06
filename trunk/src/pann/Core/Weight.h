/**
 * @file
 * Weight object
 */

#ifndef PANN_CORE_WEIGHT_H_INCLUDED
#define PANN_CORE_WEIGHT_H_INCLUDED

#include <boost/thread/mutex.hpp>
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
        explicit Weight(Float value = 1): value(value), usage_count(0) {};
        //TODO: Noncopiable
        virtual ~Weight() {};

        /**
         * Every time Link object with current Weight is created,
         * it increments usageCount counter
         * It is used later in learning algorithms for shared weights
         */
        Float get_value() const;
        void add_value(Float delta);
        void set_value(Float value);
        unsigned get_usage_count() const;
        void inc_usage_count(unsigned delta = 1);
        void dec_usage_count(unsigned delta = 1);

    private:
        Float m_value;
        unsigned m_usage_count; ///< Used by weight update algorithms for shared weights
        boost::mutex m_mutex;

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
        {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
               & BOOST_SERIALIZATION_NVP(value)
               & BOOST_SERIALIZATION_NVP(usage_count);
        };
    }; //Weight
    ADD_PTR_TYPEDEF(Weight);

}; //pann

#endif //PANN_CORE_WEIGHT_H_INCLUDED

