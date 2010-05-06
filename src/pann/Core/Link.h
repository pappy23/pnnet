/**
 * Link object
 */

#ifndef PANN_CORE_LINK_H_INCLUDED
#define PANN_CORE_LINK_H_INCLUDED

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
        Link(NeuronPtr to, WeightPtr weight, unsigned const latency = 1)
            : m_to(to), m_weight(weight), m_latency(latency) {};
        Link(const Link& rhs)
            : m_to(rhs.m_to), m_weight(rhs.m_weight), m_latency(rhs.m_latency) {};
        virtual ~Link() {};

        NeuronPtr get_to() const
        {
            return m_to;
        };

        WeightPtr get_weight() const
        {
            return m_weight;
        };

        unsigned get_latency() const
        {
            return m_latency;
        };

    private:
        NeuronPtr m_to;
        WeightPtr m_weight; /// Pointer to Weight object (might be shared between different links)
        unsigned m_latency;

    public: //private TODO
        /**
         * Link is not assign-copyable
         */
        Link& operator= (const Link& rhs)
        {
            /*
            Info()<<"Link::operator=()\n";
            to = _rhs.to;
            weight = _rhs.weight;
            latency = _rhs.latency;
            */
            return *this;
        };

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
                 & BOOST_SERIALIZATION_NVP(m_weight)
                 & BOOST_SERIALIZATION_NVP(m_latency);
            };
    }; //Link

}; //pann

#endif //PANN_CORE_LINK_H_INCLUDED

