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

        Link(Neuron & to, Weight & w, Direction direction) :
            to(to),
            w(w),
            direction(direction) { };

        ~Link() { };
        
        const Direction direction;
        Neuron & to;
        Weight & w;
    };

}; //pann

#endif //WEIGHT_H

