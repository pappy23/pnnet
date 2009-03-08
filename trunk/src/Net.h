//Net.h

#ifndef NET_H
#define NET_H 

#include "Includes.h"
#include "Object.h"
#include "Weight.h"
#include "Neuron.h"
#include "Cache.h"

namespace pann
{
    class NetCache : public Cache
    {
    public:
        typedef std::vector<Neuron*> ThreadTaskType;
        typedef std::vector<ThreadTaskType> FrontType;
        
        std::vector<FrontType> data;

        virtual void flush()
        {
            data.clear();
            touch();
        }
    };

    class Net : public Object
    {
    public:
        enum NeuronRole { WorkNeuron = 0, InputNeuron = 1, OutputNeuron = 2 };
        enum ThreadDistributionPolicy { RoundRobinPolicy, ExplicitPolicy }; //valid only for zero-thread

    protected:
        typedef std::map<int, Neuron>::iterator NeuronIter;

        int lastNeuronId; //var to add new neurons
        std::map<int, Neuron> neurons;
        std::list<NeuronIter> inputNeurons;
        std::list<NeuronIter> outputNeurons;

        NeuronIter findNeuron(int _neuronId);

        NetCache cache;

    public:
        Net();
        ~Net();

        int addNeuron(ActivationFunction::Base& _activationFunction);
        int addInputNeuron();
        int addOutputNeuron(ActivationFunction::Base& _activationFunction);
        void delNeuron(int _neuronId);

        void setNeuronRole(int _neuronId, NeuronRole _newRole);
        NeuronRole getNeuronRole(int _neuronId);

        void addConnection(int _from, int _to, float _weightValue = 1);
        void delConnection(int _from, int _to);

        std::vector<int> getInputMap();
        std::vector<int> getOutputMap();

        void setInput(std::vector<float> _input);
        std::vector<float> getOutput();

        void run();
    };

}; //pann
#endif //NET_H

