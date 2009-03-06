//Net.cpp

#include "Net.h"

using std::pair;

namespace pann
{
    Net::Net()
    {
        _lastNeuronId = 0;
    } //Net

    Net::~Net()
    {
    } //~Net

    int Net::addNeuron(ActivationFunction::Base* activationFunction)
    {
        if(!_neurons.insert( pair<int, Neuron>(++_lastNeuronId, Neuron(activationFunction)) ).second)
        {
            //Element already exist
            return 0;
        }
        
        return _lastNeuronId;
    } //addNeuron

    void Net::delNeuron(int neuronId)
    {
        _neurons.erase(neuronId);
    }

    Neuron* Net::getNeuron(int neuronId)
    {
        return &_neurons.at(neuronId);
    } //getNeuron
}; //pann

