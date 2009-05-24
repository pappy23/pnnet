/**
 * Link object
 */

#ifndef LINK_H
#define LINK_H

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"

using boost::shared_ptr;

namespace pann
{
    class Neuron;
    class Weight;

    /**
     * Link between two neurons
     */
    class Link : public Object
    {
    public:
        Link(shared_ptr<Neuron> _to, shared_ptr<Weight> _weight, unsigned const _latency = 1);
        Link(const Link& _rhs);
        virtual ~Link();

        shared_ptr<Neuron> getTo();
        const shared_ptr<Neuron> getTo() const;

        shared_ptr<Weight> getWeight();
        const shared_ptr<Weight> getWeight() const;

        unsigned getLatency() const;
    
    private:
        Link& operator=(const Link& _rhs);

    private:
        shared_ptr<Neuron> to;
        shared_ptr<Weight> weight; /// Pointer to Weight object (might be shared between different links)
        unsigned latency;

        /* Serialization */
    private:
        Link() { }; //default constructor for serialization
        //Of course we can use save_construct_data/load_construct_data, but 
        //default constructor is much simpler
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(to)
                 & BOOST_SERIALIZATION_NVP(latency)
                 & BOOST_SERIALIZATION_NVP(weight);
            };
    };

}; //pann

#endif //LINK_H

