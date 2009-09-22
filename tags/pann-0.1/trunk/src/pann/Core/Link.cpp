//Link.cpp

#include "Weight.h"
#include "Neuron.h"

#include "Link.h"

using namespace boost;

namespace pann
{
    Link::Link(NeuronPtr _to, WeightPtr _w, unsigned const _latency) 
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

    Link&
    Link::operator=(const Link& _rhs)
    {
        /*
        Info()<<"Link::operator=()\n";
        to = _rhs.to;
        weight = _rhs.weight;
        latency = _rhs.latency;
        */
        return *this;
    } //operator=

    NeuronPtr
    Link::getTo()
    {
        if(!to)
            throw NotFound()<<"Link::getTo(): Not connected\n";

        return to;
    } //getTo

    const NeuronPtr
    Link::getTo() const
    {
        if(!to)
            throw NotFound()<<"Link::getTo(): Not connected\n";

        return to;
    } //getTo

    WeightPtr
    Link::getWeight()
    {
        if(!weight)
            throw NotFound()<<"Link::getTo(): No weight\n";

        return weight;
    } //getWeight

    const WeightPtr
    Link::getWeight() const
    {
        if(!weight)
            throw NotFound()<<"Link::getTo(): No weight\n";

        return weight;
    } //getWeight

    unsigned 
    Link::getLatency() const
    {
        return latency;
    } //getLatency

}; //pann

