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
        /* Public types */
    public:
        enum Direction { in, out };

        /* Private members */
    private:
        NeuronIter to;
        Direction direction;
        WeightIter w; //!< Pointer to Weight object (might be shared between different links)
        unsigned latency;

        /* Public interface */
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

        NeuronIter getToIter()              { return to; };
        ConstNeuronIter getToIter() const   { return to; };
        Direction getDirection() const      { return direction; };
        unsigned getLatency() const         { return latency; };
        WeightIter getWeightIter()          { return w; };
    
        /* Debug */
    public:
        virtual void printDebugInfo(std::ostringstream& ost) const
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

