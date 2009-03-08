//Net.cpp

#include "Net.h"

using std::pair;
using std::map;
using std::list;
using std::vector;

namespace pann
{
    Net::Net()
    {
        lastNeuronId = 0;
    } //Net

    Net::~Net()
    {
    } //~Net

    Net::NeuronIter Net::findNeuron(int _neuronId)
    {
        NeuronIter iter = neurons.find(_neuronId);
        if(neurons.end() == iter)
            throw Exception::ObjectNotFound()<<"findNeuron(): Neuron "<<_neuronId<<" not found\n";
        
        return iter;
    } //isNeuronExist

    int Net::addNeuron(ActivationFunction::Base& _activationFunction)
    {
        cache.flush();

        if(!neurons.insert( pair<int, Neuron>(++lastNeuronId, Neuron(_activationFunction)) ).second)
            throw Exception::ElementExists()<<"Net::addNeuron(): insertion of neuron "<<lastNeuronId<<" failed\n";
        
        return lastNeuronId;
    } //addNeuron

    int Net::addInputNeuron()
    {
        int neuronId = addNeuron(ActivationFunction::Linear::Instance());
        setNeuronRole(neuronId, Net::InputNeuron);

        return neuronId;
    } //addInputNeuron

    int Net::addOutputNeuron(ActivationFunction::Base& _activationFunction)
    {
        int neuronId = addNeuron(_activationFunction);
        setNeuronRole(neuronId, Net::OutputNeuron);

        return neuronId;
    } //addOutputNeuron

    void Net::delNeuron(int _neuronId)
    {
        cache.flush();

        if( !neurons.erase(_neuronId) )
            throw Exception::ObjectNotFound()<<"Net::delNeuron(): neuron "<<_neuronId<<" not found\n";
    } //delNeuron

    void Net::setNeuronRole(int _neuronId, NeuronRole _newRole)
    {
        cache.flush();

        NeuronIter iter = findNeuron(_neuronId);

        list< NeuronIter >::iterator inputIter = find(inputNeurons.begin(), inputNeurons.end(), iter);
        list< NeuronIter >::iterator outputIter = find(outputNeurons.begin(), outputNeurons.end(), iter);

        switch(_newRole)
        {
            case InputNeuron:
                if(outputIter != outputNeurons.end())
                    outputNeurons.erase(outputIter);
                if(inputIter == inputNeurons.end())
                    inputNeurons.push_back(iter);
                break;
            case OutputNeuron:
                if(inputIter != inputNeurons.end())
                    inputNeurons.erase(inputIter);
                if(outputIter == outputNeurons.end())
                    outputNeurons.push_back(iter);
                break;
            case WorkNeuron:
                if(inputIter != inputNeurons.end())
                    inputNeurons.erase(inputIter);
                if(outputIter != outputNeurons.end())
                    outputNeurons.erase(outputIter);
                break;
        }
    } //setNeuronRole

    Net::NeuronRole Net::getNeuronRole(int _neuronId)
    {
        /*
         * 0 - work neuron
         * 1 - work+input
         * 2 - work+output
         */
        int role = 0;

        NeuronIter iter = findNeuron(_neuronId);

        if(find(inputNeurons.begin(), inputNeurons.end(), iter) != inputNeurons.end())
            role+=1;
        if(find(outputNeurons.begin(), outputNeurons.end(), iter) != outputNeurons.end())
            role+=2;

        return (NeuronRole)role;
    } //getNeuronRole

    void Net::addConnection(int _from, int _to, float _weightValue)
    {
        cache.flush();

        Neuron& from = findNeuron(_from)->second;
        Neuron& to = findNeuron(_to)->second;

        from.connect(to, _weightValue);
    } //addConnection

    void Net::delConnection(int _from, int _to)
    {
        cache.flush();

        Neuron& from = findNeuron(_from)->second;
        Neuron& to = findNeuron(_to)->second;

        from.disconnect(to);        
    } //delConnection

    std::vector<int> Net::getInputMap()
    {
        vector<int> result;

        list< NeuronIter >::iterator iter = inputNeurons.begin();
        for(; iter != inputNeurons.end(); ++iter)
            result.push_back((*iter)->first);

        return result;
    } //getInputMap

    std::vector<int> Net::getOutputMap()
    {
        vector<int> result;

        list< NeuronIter >::iterator iter = outputNeurons.begin();
        for(; iter != outputNeurons.end(); ++iter)
            result.push_back((*iter)->first);

        return result;
    } //getOutputMap

    void Net::setInput(vector<float> _input)
    {
        if(_input.size() < inputNeurons.size())
            throw Exception::SizeMismatch()<<"setInput(): Supplied input size is smaller then number of input neurons\n";

        if(_input.size() > inputNeurons.size())
            Exception::Warning()<<"setInput(): Input size is bigger then input neurons count. Check getInputMap() output\n";

        list< NeuronIter >::iterator it = inputNeurons.begin();
        for(int i = 0; it != inputNeurons.end(); ++it, ++i)
        {
            (*it)->second.receptiveField = _input[i];
        }
    } //setInput

    vector<float> Net::getOutput()
    {
        vector<float> result;
        list< NeuronIter >::iterator it = outputNeurons.begin();
        for(; it != outputNeurons.end(); ++it)
            result.push_back((*it)->second.activationValue);

        return result;
    } //setInput

    void Net::run()
    {
        ////put inputNeurons to front
        if( !cache.isOk() )
        {
            cache.flush();
            
            vector<int> rawFront;
            //vector< NeuronIter >::iterator iter = inputNeurons.begin();
            //for(; iter != InputNeurons.end(); ++iter)
            BOOST_FOREACH( NeuronIter iter, inputNeurons )
            {
                rawFront.push_back(iter->first); 
            }
        }


        ////while(front.size() > 0)
        {
            ////distribute front neurons between processes
            ////write this information into cache
            ////Every thread gets reference to his own vector of references to neurons
            ////start working threads
            ////while they process neurons in front, determine what neurons are next front
            ////write that information to cache
            ////delete redundant neurons from front
            ////new front is formed or loaded from cache
            ////wait for threads to finish
            ////that's all. continue while loop
        }
    } //run
/*
    Neuron& Net::getNeuron(int _neuronId)
    {
        NeuronIter i = neurons.find(_neuronId);
        if(i == neurons.end())
            throw Exception::ObjectNotFound()<<"Net::getNeuron(): neuron "<< _neuronId<<"not found\n";

        return i->second;
    } //getNeuron
*/

}; //pann

