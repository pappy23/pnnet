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
        const Neuron* _to;
        boost::shared_ptr<Weight> _w;

    public:
        Link(Neuron* to, const Direction direction, Weight* w) :
            _to(to),
            _direction(direction),
            _w(w) { };

        ~Link() { };

        inline Direction getDirection() { return _direction; };
        inline const Neuron* getTo() { return _to; };
        inline const boost::shared_ptr<Weight> getW() { return _w; };
    };

}; //pann

#endif //WEIGHT_H

