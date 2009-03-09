//Net.h

#ifndef NET_H
#define NET_H 

#include "Includes.h"
#include "Object.h"
#include "Neuron.h"
#include "Cache.h"
#include "Util.h"

namespace pann
{
    class NetCache : public Cache
    {
    public:
        typedef std::vector<NeuronIter> ThreadTaskType;
        typedef std::vector<ThreadTaskType> FrontType;
        
        std::vector<FrontType> data;

        virtual void flush()
        {
            data.clear();
            touch();
        }

        //Print cache content for debug purposes
        void debugPrint()
        {
            for(int layers = 0; layers < data.size(); ++layers)
            {
                std::cout<<"Layer #"<<layers<<std::endl;
                for(int threads = 0; threads < data[layers].size(); ++threads)
                {
                    std::cout<<"  Thread "<<threads<<": ";
                    for(int n = 0; n < data[layers][threads].size(); ++n)
                        std::cout<<data[layers][threads][n]->first<<" ";
                    std::cout<<std::endl;
                }
                std::cout<<std::endl;
            }
        }
    };

    class Net : public Object
    {
    public:
        enum NeuronRole { WorkNeuron = 0, InputNeuron = 1, OutputNeuron = 2 };

    protected:

        int threadCount;
        int lastNeuronId; //var to add new neurons
        std::map<int, Neuron> neurons;
        std::list<NeuronIter> inputNeurons;  //Iterators to map<> neurons
        std::list<NeuronIter> outputNeurons; //Iterators to map<> neurons 

        NeuronIter findNeuron(int _neuronId);
        void formatFront(std::vector<NeuronIter>& _raw);


    public:
        //DEBUG!! put it in protected section
        NetCache cache;

        Net();
        Net(int _threads);
        ~Net();

        int getThreadCount();
        void setThreadCount(int _threads);

        int addNeuron(ActivationFunction::Base& _activationFunction);
        int addInputNeuron();
        int addOutputNeuron(ActivationFunction::Base& _activationFunction);
        void delNeuron(int _neuronId);

        void setNeuronRole(int _neuronId, NeuronRole _newRole);
        NeuronRole getNeuronRole(int _neuronId);

        void addConnection(int _from, int _to, Float _weightValue = 1);
        void delConnection(int _from, int _to);

        std::vector<int> getInputMap();
        std::vector<int> getOutputMap();

        void setInput(std::vector<Float> _input);
        std::vector<Float> getOutput();

        void run();
    };

}; //pann
#endif //NET_H

