/**
 * Link object
 */

#ifndef LINK_H
#define LINK_H

#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"

namespace pann
{
    /**
     * Link between two neurons
     */
    class Link : public Object
    {
    public:
        Link(NeuronPtr _to, WeightPtr _weight, unsigned const _latency = 1);
        Link(const Link& _rhs);
        virtual ~Link();

        const NeuronPtr& getTo();
        const NeuronPtr& getTo() const;

        WeightPtr getWeight();
        const WeightPtr getWeight() const;

        unsigned getLatency() const;

    private:
        /**
         * Link is not assign-copyable
         */
        Link& operator=(const Link& _rhs);

    private:
        NeuronPtr to;
        WeightPtr weight; /// Pointer to Weight object (might be shared between different links)
        unsigned latency;

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
                 & BOOST_SERIALIZATION_NVP(latency)
                 & BOOST_SERIALIZATION_NVP(weight);
            };
    };

}; //pann

#endif //LINK_H

