/**
 * @file
 * Link object
 */

#ifndef LINK_H
#define LINK_H

#include "Includes.h"
#include "Object.h"
#include "Weight.h"
#include "Neuron.h"

namespace pann
{
    class Neuron;

    //! Link between two neurons
    class Link : public Object
    {
    public:
        enum Direction { in, out };

    protected:
        Direction direction;
        Neuron& to;
        boost::shared_ptr<Weight> w; //!< Pointer to Weight object (may be shared between different links)

    public:
        Link(Neuron& _to, const Direction _direction, Weight* _w) :
            to(_to),
            direction(_direction),
            w(_w) { };

        ~Link() { };

        inline Direction getDirection() const { return direction; };
        inline Neuron& getTo() const { return to; };
        inline const boost::shared_ptr<Weight> getW() const { return w; };
    };

}; //pann

#endif //WEIGHT_H

