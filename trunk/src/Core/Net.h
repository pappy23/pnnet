//Net.h

#ifndef NET_H
#define NET_H

#include "Includes.h"
#include "Object.h"
#include "Neuron.h"
#include "Cache.h"
#include "Util.h"
#include "Runner.h"

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

        //! Print cache content for debug purposes
        void printDebugInfo(std::ostringstream& ost)
        {
            for(UINT layers = 0; layers < data.size(); ++layers)
            {
                ost<<"Layer #"<<layers<<std::endl;
                for(UINT threads = 0; threads < data[layers].size(); ++threads)
                {
                    ost<<"  Thread "<<threads<<": ";
                    for(UINT n = 0; n < data[layers][threads].size(); ++n)
                        ost<<data[layers][threads][n]->first<<" ";
                    ost<<std::endl;
                }
                ost<<std::endl;
            }
        }

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & data;
            };
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

        static void threadBase(Runner* _runner, std::vector<NeuronIter> _task)
        {
            for(UINT i = 0; i < _task.size(); i++)
                _runner->run(_task[i]);
        } //threadBase


        NetCache cache;

    public:
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

        void setNeuronOwner(int _neuron, int _owner);
        int getNeuronOwner(int _neuron);

        void addConnection(int _from, int _to, Float _weightValue = 1);
        void delConnection(int _from, int _to);

        std::vector<int> getInputMap();
        std::vector<int> getOutputMap();

        void setInput(std::vector<Float> _input);
        std::vector<Float> getOutput();

        void run(Runner* _runner);

        void printDebugInfo(std::ostringstream& ost);

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);
                ar & lastNeuronId;
                ar & threadCount;
                ar & cache;
                ar & neurons;
                ar & inputNeurons;
                ar & outputNeurons;
            };
    };

}; //pann
#endif //NET_H

