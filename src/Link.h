//Link.h

#ifndef LINK_H
#define LINK_H

#include "Object.h"
#include "Neuron.h"
#include "Weight.h"

namespace pann
{

    class Link : public Object
    {
    public:
        Link(Neuron & to, Weight & w, Direction direction) :
            this->to(to),
            this->w(w),
            this->direction(direction) { };

        ~Link() { };

        enum Direction { in, out; };
        
        const Direction direction;
        Neuron & to;
        Weight & w;
    };

}; //pann

#endif //WEIGHT_H

