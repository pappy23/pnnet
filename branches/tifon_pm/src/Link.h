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
        Direction _direction;
        Neuron& _to;
        boost::shared_ptr<Weight> _w;

    public:
        Link(Neuron& to, const Direction direction, Weight* w) :
            _to(to),
            _direction(direction),
            _w(w) { };

        ~Link() { };

        inline Direction getDirection() const { return _direction; };
        inline Neuron& getTo() const { return _to; };
        inline const boost::shared_ptr<Weight> getW() const { return _w; };
    };

}; //pann

#endif //WEIGHT_H

