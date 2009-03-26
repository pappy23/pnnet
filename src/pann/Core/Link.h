/**
 * @file
 * Link object
 */

#ifndef LINK_H
#define LINK_H

#include "Includes.h"
#include "Object.h"
#include "Weight.h"

namespace pann
{
    class Neuron;

    //! Link between two neurons
    class Link : public Object
    {
        /* Public types */
    public:
        enum Direction { in, out };

        /* Private members */
    private:
        Neuron* to;
        Direction direction;
        Weight* w; //!< Pointer to Weight object (might be shared between different links)
        unsigned latency;

        /* Public interface */
    public:
        Link(Neuron* _to, const Direction _direction, Weight* _w, unsigned const _latency = 1)
        virtual ~Link();

        Neuron* getTo();  
        const Neuron*  getTo() const;

        Direction getDirection() const;
        unsigned getLatency() const;
        Weight* getWeight();   
    
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
                 & BOOST_SERIALIZATION_NVP(direction)
                 & BOOST_SERIALIZATION_NVP(w)
                 & BOOST_SERIALIZATION_NVP(latency);
            };
    };

}; //pann

#endif //LINK_H

