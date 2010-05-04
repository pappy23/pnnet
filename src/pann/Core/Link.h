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
            : to(to), weight(weight), latency(latency) {};
        Link(const Link& _rhs)
            : to(_rhs.to), weight(rhs.weight), latency(_rhs.latency) {};
        virtual ~Link() {};

        NeuronPtr to;
        WeightPtr weight; /// Pointer to Weight object (might be shared between different links)
        unsigned latency;

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
                 & BOOST_SERIALIZATION_NVP(to)
                 & BOOST_SERIALIZATION_NVP(weight)
                 & BOOST_SERIALIZATION_NVP(latency);
            };
    };

}; //pann

#endif //PANN_CORE_LINK_H_INCLUDED

