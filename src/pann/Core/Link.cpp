//Link.cpp

#include "Link.h"

#include "Weight.h"
#include "Neuron.h"

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
    Link::getTo() throw(E<Exception::ObjectNotFound>)
    {
        if(!to)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): Not connected\n";

        return *to;
    } //getTo

    const Neuron&
    Link::getTo() const throw(E<Exception::ObjectNotFound>)
    {
        if(!to)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): Not connected\n";

        return *to;
    } //getTo

    Weight&
    Link::getWeight() throw(E<Exception::ObjectNotFound>)
    {
        if(!weight)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): No weight\n";

        return *weight;
    } //getWeight

    const Weight&
    Link::getWeight() const throw(E<Exception::ObjectNotFound>)
    {
        if(!weight)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): No weight\n";

        return *weight;
    } //getWeight

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

