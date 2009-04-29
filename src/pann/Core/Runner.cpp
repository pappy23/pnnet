/*
 * @file
 * Generic runner realization
 */

#include "Runner.h"

#include "Net.h"
#include "Neuron.h"

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
        if(!_neuron.hasActivationFunction())
            return;

        _neuron.fire();
    } //run

    RunDirection
    FeedforwardPropagationRunner::getDirection()
    {
        return ForwardRun;
    } //getDirection

}; //pann
