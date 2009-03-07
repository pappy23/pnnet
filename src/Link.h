//Link.h

#ifndef LINK_H
#define LINK_H

#include "Includes.h"
#include "Object.h"
#include "Weight.h"
#include "Neuron.h"

namespace pann
{
    class Neuron;

    class Link : public Object
    {
    public:
        enum Direction { in, out };

    private:
        Direction direction;
        Neuron& to;
        boost::shared_ptr<Weight> w;

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

