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
        UINT latency;
        WeightIter w; //!< Pointer to Weight object (might be shared between different links)

    public:
        Link(const NeuronIter _to, const Direction _direction, WeightIter _w, UINT _latency = 1) :
            to(_to),
            direction(_direction),
            w(_w),
            latency(_latency)
        {
            w->second.usageCount++;
        };

        ~Link()
        {
            w->second.usageCount--;
        };

        NeuronIter getTo()       { return to; };
        Direction getDirection() { return direction; };
        UINT getLatency()        { return latency; };
        WeightIter getWeight()   { return w; };
    
    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"  Link\n";
            ost<<"   direction: "<<direction<<std::endl;
            //ost<<"   to: "<<to->first<<std::endl; - Neuron - incomplete class
            w->second.printDebugInfo(ost);
        }
    };

}; //pann

#endif //LINK_H

