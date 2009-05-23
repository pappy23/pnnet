//Link.cpp

#include "Weight.h"
#include "Neuron.h"

#include "Link.h"

using namespace boost;

namespace pann
{
    Link::Link(shared_ptr<Neuron> _to, shared_ptr<Weight> _w, unsigned const _latency) 
        : to(_to), weight(_w), latency(_latency)
    {
        weight->incUsageCount();
    } //Link

    Link::Link(const Link& _rhs)
        : to(_rhs.to), weight(_rhs.weight), latency(_rhs.latency)
    {
        weight->incUsageCount();
    } //Link

    Link::~Link()
    {
        weight->decUsageCount();
    } //~Link

/*
    Link&
    Link::operator=(Link const & _rhs)
    {
        to = _rhs.to;
        weight = _rhs.weight;
        latency = _rhs.latency;
        std::cout<<"=";

        return *this;
    } //operator=
*/

    shared_ptr<Neuron>
    Link::getTo()
    {
        if(!to)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): Not connected\n";

        return to;
    } //getTo

    const shared_ptr<Neuron>
    Link::getTo() const
    {
        if(!to)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): Not connected\n";

        return to;
    } //getTo

    shared_ptr<Weight>
    Link::getWeight()
    {
        if(!weight)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): No weight\n";

        return weight;
    } //getWeight

    const shared_ptr<Weight>
    Link::getWeight() const
    {
        if(!weight)
            throw E<Exception::ObjectNotFound>()<<"Link::getTo(): No weight\n";

        return weight;
    } //getWeight

    unsigned 
    Link::getLatency() const
    {
        return latency;
    } //getLatency

}; //pann

