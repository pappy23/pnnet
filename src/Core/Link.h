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
        Link(Neuron* _to, const Direction _direction, Weight* _w, unsigned const _latency = 1) :
            to(_to),
            direction(_direction),
            w(_w),
            latency(_latency)
        {
        };

        ~Link()
        {
        };

        Neuron* getTo()                { return to; };
        const Neuron*  getTo() const   { return to; };
        Direction getDirection() const { return direction; };
        unsigned getLatency() const    { return latency; };
        Weight* getWeight()            { return w; };
    
        /* Serialization */
    private:
        Link() { }; //default constructor for serialization
        //Of course we can use save_construct_data/load_construct_data, but 
        //default constructor is much simpler
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);
                ar & to;
                ar & direction;
                ar & w;
                ar & latency;
            };
    };

}; //pann

#endif //LINK_H

