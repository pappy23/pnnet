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

    public:
        virtual void printDebugInfo(std::ostringstream& ost)
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

    private:
        int threadCount;
        int lastNeuronId; //var to add new neurons
        int lastWeightId; //var to add new weights
        std::map<int, Neuron> neurons;
        std::map<int, Weight> weights;
        std::list<NeuronIter> inputNeurons;  //Iterators to map<> neurons
        std::list<NeuronIter> outputNeurons; //Iterators to map<> neurons
        NetCache cache;

    private:
        NeuronIter findNeuron(int _neuronId);
        void formatFront(std::vector<NeuronIter>& _raw);

        //TODO: get _task not by copying but by pointer or boost::ref
        static void threadBase(Runner* _runner, std::vector<NeuronIter> _task)
        {
            for(UINT i = 0; i < _task.size(); i++)
                _runner->run(_task[i]);
        };

    public:
        Net();
        Net(int _threads);
        ~Net();

        int getThreadCount();
        void setThreadCount(int _threads);

        int addNeuron(ActivationFunction::Base* _activationFunction);
        int addInputNeuron();
        int addOutputNeuron(ActivationFunction::Base* _activationFunction);
        void delNeuron(int _neuronId);

        void setNeuronRole(int _neuronId, NeuronRole _newRole);
        NeuronRole getNeuronRole(int _neuronId);

        void setNeuronOwner(int _neuron, int _owner);
        int getNeuronOwner(int _neuron);

        void addConnection(int _from, int _to, Float _weightValue = 1);
        void delConnection(int _from, int _to);

        std::vector<int> getInputMap();
        std::vector<int> getOutputMap();

        void setInput(const std::vector<Float>& _input);
        std::vector<Float> getOutput();

        void run(Runner* _runner);

    public:
        void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"Net\n";
            ost<<" threadsCount: "<<threadCount<<std::endl;
            ost<<" lastNeuronId: "<<lastNeuronId<<std::endl;
            ost<<" lastWeightId: "<<lastWeightId<<std::endl;
            ost<<" neurons: ";
            NeuronIter it = neurons.begin();
            for(; it != neurons.end(); ++it)
                ost<<it->first<<" ";
            ost<<"\n weights: ";
            WeightIter wit = weights.begin();
            for(; wit != weights.end(); ++wit)
                ost<<wit->first<<" ";
            ost<<"\n inputNeurons: ";
            std::list<NeuronIter>::iterator it2 = inputNeurons.begin();
            for(; it2 != inputNeurons.end(); ++it2)
                ost<<(*it2)->first<<" ";
            ost<<"\n outputNeurons: ";
            std::list<NeuronIter>::iterator it3 = outputNeurons.begin();
            for(; it3 != outputNeurons.end(); ++it3)
                ost<<(*it3)->first<<" ";
            ost<<"\n\n neurons: ";
            for(it = neurons.begin(); it != neurons.end(); ++it)
                it->second.printDebugInfo(ost);
            ost<<"\n\n Cache:\n";
            cache.printDebugInfo(ost);
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void save(Archive & ar, const unsigned int version) const
            {
                ar & boost::serialization::base_object<Object>(*this);
                ar & lastNeuronId;
                ar & lastWeightId;
                ar & threadCount;
                //ar & cache; - dont's save it
                ar & neurons;
                ar & weights;

                //save links 'to' field for every neuron
                for(std::map<int, Neuron>::const_iterator iter = neurons.begin(); iter != neurons.end(); ++iter)
                {
                    UINT size = iter->second.links.size();
                    ar & size;
                    BOOST_FOREACH( const Link& l, iter->second.links )
                    {
                        Link& link = const_cast<Link&>(l);
                        UINT to = link.getToIter()->first;
                        UINT w  = link.getWeightIter()->first;
                        UINT dir= (UINT)link.getDirection();
                        UINT latency = (UINT)link.getLatency();
                        ar & to;
                        ar & w;
                        ar & dir;
                        ar & latency;
                    }
                }
                
                UINT size;
                size = inputNeurons.size();
                ar & size;
                BOOST_FOREACH( NeuronIter iter, inputNeurons )
                {
                    UINT id = iter->first;
                    ar & id;
                }

                size = outputNeurons.size();
                ar & size;
                BOOST_FOREACH( NeuronIter iter, outputNeurons )
                {
                    UINT id = iter->first;
                    ar & id;
                }
            };

        template<class Archive>
            void load(Archive & ar, const unsigned int version)
            {
                cache.touch();

                ar & boost::serialization::base_object<Object>(*this);
                ar & lastNeuronId;
                ar & lastWeightId;
                ar & threadCount;
                //ar & cache; - don't load it
                ar & neurons;
                ar & weights;
               
                //load links 'to' field for every neuron
                for(NeuronIter iter = neurons.begin(); iter != neurons.end(); ++iter)
                {
                    UINT size;
                    ar & size;
                    for(int i = 0; i < size; i++)
                    {
                        UINT to, w, dir, latency;
                        ar & to;
                        ar & w;
                        ar & dir;
                        ar & latency;
                        NeuronIter to_it = neurons.find(to);
                        WeightIter  w_it = weights.find(w);
                        if(to_it == neurons.end() || w_it == weights.end())
                            throw Exception::FilesystemError()<<"Net::load(): can't load Net object. "
                                                                              "Archive possibly damaged\n";
                        iter->second.links.push_back(Link(to_it, (Link::Direction)dir, w_it, latency));
                   }
                }

                UINT size;
                ar & size; 
                for(UINT i = 0; i < size; i++)
                {
                    UINT id; ar & id;
                    NeuronIter iter = neurons.find(id);
                    inputNeurons.push_back(iter);
                    if(iter == neurons.end())
                        throw Exception::FilesystemError()<<"Net::load(): can't load Net object. Archive possibly damaged\n";
                }

                ar & size; 
                for(UINT i = 0; i < size; i++)
                {
                    UINT id; ar & id;
                    NeuronIter iter = neurons.find(id);
                    outputNeurons.push_back(iter);
                    if(iter == neurons.end())
                        throw Exception::FilesystemError()<<"Net::load(): can't load Net object. Archive possibly damaged\n";
                }
            };

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

}; //pann
#endif //NET_H

