//Neuron.cpp

#include "Neuron.h"

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base& _activationFunction) :
            activationFunction(_activationFunction), 
            receptiveField(0), 
            activationValue(_activationFunction.f(0))
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    float Neuron::activate()
    {
        return activationValue = activationFunction.f(receptiveField);
    } //activate

    void Neuron::connectTo(Neuron& _to, Link::Direction _direction = Link::out, float _weightValue = 1)
    {
        connectTo(_to, new Weight(_weightValue), _direction); 
    } //connectTo

    void Neuron::connectTo(Neuron& _to, Weight* _weight, Link::Direction _direction = Link::out)
    {
        //ACHTUNG!!! Parallel links ARE allowed
        links.push_back( Link(_to, _direction, _weight) ); //feedforward link
        _direction == Link::in ? _direction = Link::out : _direction = Link::in;
        _to.links.push_back( Link(*this, _direction, _weight) ); //backpropagation link
    } //connectTo

}; //pann
