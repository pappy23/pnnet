//Link.cpp

#include "Link.h"

namespace pann
{
    Link::Link(Neuron* _to, const Direction _direction, Weight* _w, unsigned const _latency = 1)
    {
        to = _to;
        direction = _direction;
        w = _w;
        latency = _latency;

        w->usageCount++;
    } //Link

    ~Link()
    {
        if( (w->usageCount--) == 0)
            delete w;
    } //~Link

    Neuron*
    Link::getTo()
    {
        return to;
    } //getTo

    const Neuron*
    Link::getTo() const
    {
        return to;
    } //getTo

    Direction
    Link::getDirection() const
    {
        return direction;
    } //getDirection
    unsigned 
    getLatency() const
    {
        return latency;
    } //getLatency
    
    Weight*
    getWeight()
    {
        return w;
    } //getWeight

}; //pann

