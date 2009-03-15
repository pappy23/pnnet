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
    class Net;

    //! Link between two neurons
    class Link : public Object
    {
    public:
        enum Direction { in, out };

    private:
        NeuronIter to;
        Direction direction;
        WeightIter w; //!< Pointer to Weight object (might be shared between different links)
        unsigned latency;

    public:
        Link(const NeuronIter _to, const Direction _direction, WeightIter _w, unsigned const _latency = 1) :
            to(_to),
            direction(_direction),
            w(_w),
            latency(_latency)
        {
        };

        ~Link()
        {
        };

        NeuronIter getToIter()     { return to; };
        Direction getDirection()   { return direction; };
        unsigned getLatency()      { return latency; };
        WeightIter getWeightIter() { return w; };
    
    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"  Link\n";
            ost<<"   direction: "<<direction<<std::endl;
            ost<<"   latency: "<<latency<<std::endl;
            //ost<<"   to: "<<to->first<<std::endl; - Neuron - incomplete class
            w->second.printDebugInfo(ost);
        }
    };

}; //pann

#endif //LINK_H

