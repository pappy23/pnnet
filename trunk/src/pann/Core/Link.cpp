//Link.cpp

#include "Link.h"

namespace pann
{
    Link::Link(Neuron* _to, const Link::Direction _direction, Weight* _w, unsigned const _latency) throw()
    {
        to = _to;
        direction = _direction;
        w = _w;
        latency = _latency;

        w->usageCount++;
    } //Link

    Link::~Link() throw()
    {
        if( (w->usageCount--) == 0)
            delete w;
    } //~Link

    Neuron*
    Link::getTo() throw()
    {
        return to;
    } //getTo

    const Neuron*
    Link::getTo() const throw()
    {
        return to;
    } //getTo

    Link::Direction
    Link::getDirection() const throw()
    {
        return direction;
    } //getDirection
    unsigned 
    Link::getLatency() const throw()
    {
        return latency;
    } //getLatency
    
    Weight*
    Link::getWeight() throw()
    {
        return w;
    } //getWeight

}; //pann

