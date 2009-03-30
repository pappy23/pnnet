/*
 * @file
 * Generic runner realization
 */

#include "Runner.h"

namespace pann
{
    Runner* NullRunner::self = 0;

    NullRunner::NullRunner()
    {
    } //NullRunner
    
    NullRunner::~NullRunner()
    {
    } //~NullRunner

    Runner*
    NullRunner::Instance()
    {
        if(!self)
            self = new NullRunner();

        return self;
    } //Instance

    void
    NullRunner::run(Neuron* _neuron, const Net* _net)
    {
    } //run

    RunDirection
    NullRunner::getDirection()
    {
        return ForwardRun;
    } //getDirection

    Runner* NullBackpropagationRunner::self = 0;

    NullBackpropagationRunner::NullBackpropagationRunner()
    {
    } //NullBackpropagationRunner

    NullBackpropagationRunner::~NullBackpropagationRunner()
    {
    } //~NullBackpropagationRunner

    Runner*
    NullBackpropagationRunner::Instance()
    {
        if(!self)
            self = new NullBackpropagationRunner();

        return self;
    } //Instance

    void
    NullBackpropagationRunner::run(Neuron* _neuron, const Net* _net)
    {
    } //run

    RunDirection
    NullBackpropagationRunner::getDirection()
    {
        return BackwardRun;
    } //getDirection

    Runner* FeedforwardPropagationRunner::self = 0;

    FeedforwardPropagationRunner::FeedforwardPropagationRunner()
    {
    } //FeedforwardPropagationRunner
    
    FeedforwardPropagationRunner::~FeedforwardPropagationRunner()
    {
    } //~FeedforwardPropagationRunner

    Runner*
    FeedforwardPropagationRunner::Instance()
    {
        if(!self)
            self = new FeedforwardPropagationRunner();

        return self;
    } //Instance

    void
    FeedforwardPropagationRunner::run(Neuron* _neuron, const Net* _net)
    {
        if(!_neuron->getActivationFunction())
            return;

        Float receptiveField = 0;
        if(_neuron->bias)
            receptiveField += _neuron->bias->value;

        BOOST_FOREACH( Link& link, _neuron->links )
        {
            if(link.getDirection() == Link::in)
                receptiveField += link.getTo()->activationValue * link.weight->value;
        }

        _neuron->activationValue = _neuron->getActivationFunction()->f(receptiveField);
    } //run

    RunDirection
    FeedforwardPropagationRunner::getDirection()
    {
        return ForwardRun;
    } //getDirection

}; //pann

