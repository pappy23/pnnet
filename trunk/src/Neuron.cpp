//Neuron.cpp

#include "Neuron.h"

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base* activationFunction) :
            _activationFunction(activationFunction), 
            receptiveField(0), 
            activationValue(activationFunction->f(0))
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    float Neuron::activate()
    {
        return activationValue = _activationFunction->f(receptiveField);
    } //activate

}; //pann
