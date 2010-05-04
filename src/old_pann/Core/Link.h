/**
 * Link object
 */

#ifndef PANN_CORE_LINK_H_INCLUDED
#define PANN_CORE_LINK_H_INCLUDED

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Weight.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Neuron);
    /**
     * Link between two neurons
     */
    class Link : public Object
    {
    public:
        Link(NeuronPtr _to, WeightPtr _weight, unsigned const _latency = 1)
            : m_to(_to), m_weight(_weight), m_latency(_latency)
        {
            if(!_to || !_weight)
                Exception()<<"Link::Link(): empty ptr received";

            m_weight->incUsageCount();
        }

        Link(const Link& _rhs)
            : m_to(_rhs.m_to), m_weight(_rhs.m_weight), m_latency(_rhs.m_latency)
        {
            m_weight->incUsageCount();
        }

        virtual ~Link() {};

        NeuronPtr getTo() const { return m_to; };
        WeightPtr getWeight() const { return m_weight; };
        unsigned getLatency() const { return m_latency; };

    private:
        /**
         * Link is not assign-copyable
         */
        Link& operator=(const Link& _rhs)
        {
            /*
            Info()<<"Link::operator=()\n";
            to = _rhs.to;
            weight = _rhs.weight;
            latency = _rhs.latency;
            */
            return *this;
        };

    private:
        NeuronPtr m_to;
        WeightPtr m_weight; /// Pointer to Weight object (might be shared between different links)
        unsigned m_latency;

        /* Serialization */
    private:
        /**
         * Default constructor for serialization
         * Of course we can use save_construct_data/load_construct_data, but
         * default constructor is much simpler
         */
        Link() { };

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(m_to)
                 & BOOST_SERIALIZATION_NVP(m_latency)
                 & BOOST_SERIALIZATION_NVP(m_weight);
            };
    };

}; //pann

#endif //PANN_CORE_LINK_H_INCLUDED

