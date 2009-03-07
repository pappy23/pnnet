//Net.cpp

#include "Net.h"

using std::pair;
using std::map;

namespace pann
{
    Net::Net()
    {
        lastNeuronId = 0;
    } //Net

    Net::~Net()
    {
    } //~Net

    int Net::addNeuron(ActivationFunction::Base& _activationFunction)
    {
        if(!neurons.insert( pair<int, Neuron>(++lastNeuronId, Neuron(_activationFunction)) ).second)
            throw Exception::ElementExists()<<"Net::addNeuron(): insertion of neuron "<<lastNeuronId<<" failed\n";
        
        return lastNeuronId;
    } //addNeuron

    void Net::delNeuron(int _neuronId)
    {
        if(!neurons.erase(_neuronId))
            throw Exception::ObjectNotFound()<<"Net::delNeuron(): neuron "<<_neuronId<<" not found\n";
    }

    Neuron& Net::getNeuron(int _neuronId)
    {
        map<int, Neuron>::iterator i = neurons.find(_neuronId);
        if(i == neurons.end())
            throw Exception::ObjectNotFound()<<"Net::getNeuron(): neuron "<< _neuronId<<"not found\n";

        return i->second;
    } //getNeuron
}; //pann

