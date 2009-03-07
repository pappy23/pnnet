//Neuron.cpp

#include "Neuron.h"

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base& activationFunction) :
            _activationFunction(activationFunction), 
            receptiveField(0), 
            activationValue(activationFunction.f(0))
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    float Neuron::activate()
    {
        return activationValue = _activationFunction.f(receptiveField);
    } //activate

    void Neuron::connectTo(Neuron& to, Link::Direction direction = Link::out, float weightValue = 1)
    {
        connectTo(to, new Weight(weightValue), direction); 
    } //connectTo

    void Neuron::connectTo(Neuron& to, Weight* weight, Link::Direction direction = Link::out)
    {
       _links.push_back( Link(to, direction, weight) ); //feedforward link
       direction == Link::in ? direction = Link::out : direction = Link::in;
       to._links.push_back( Link(*this, direction, weight) ); //backpropagation link
    } //connectTo

}; //pann
