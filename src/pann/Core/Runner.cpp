/*
 * @file
 * Generic runner realization
 */

#include "Runner.h"

namespace pann
{
    Runner* FeedforwardPropagationRunner::self = 0;

    FeedforwardPropagationRunner::FeedforwardPropagationRunner()
    {
    } //FeedforwardPropagationRunner
    
    FeedforwardPropagationRunner::~FeedforwardPropagationRunner()
    {
    } //~FeedforwardPropagationRunner

    Runner&
    FeedforwardPropagationRunner::Instance()
    {
        if(!self)
            self = new FeedforwardPropagationRunner();

        return *self;
    } //Instance

    void
    FeedforwardPropagationRunner::run(Neuron& _neuron, const Net& _net)
    {
        if(!_neuron.getActivationFunction())
            return;

        Float receptiveField = 0;
        if(_neuron.bias)
            receptiveField += (*_neuron.bias)[Weight::value];

        BOOST_FOREACH( Link& link, _neuron.links )
        {
            if(link.getDirection() == Link::in)
                receptiveField += link.getTo()[Neuron::activationValue] * (*link.weight)[Weight::value];
        }

        _neuron[Neuron::activationValue] = _neuron.getActivationFunction()->f(receptiveField);
    } //run

    RunDirection
    FeedforwardPropagationRunner::getDirection()
    {
        return ForwardRun;
    } //getDirection

}; //pann

