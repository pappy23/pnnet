//Link.cpp

#include "Link.h"

namespace pann
{
    Link::Link(Neuron* _to, const Link::Direction _direction, Weight* _w, unsigned const _latency) throw()
    {
        to = _to;
        direction = _direction;
        weight = _w;
        latency = _latency;
    } //Link

    Link::~Link() throw()
    {
    } //~Link

    Neuron&
    Link::getTo() throw()
    {
        return *to;
    } //getTo

    const Neuron&
    Link::getTo() const throw()
    {
        return *to;
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

}; //pann

