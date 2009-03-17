//Net.h

#ifndef NET_H
#define NET_H

#include "Includes.h"
#include "Object.h"
#include "Neuron.h"
#include "Cache.h"
#include "Util.h"
#include "Runner.h"

//TODO: add shared weight function addConnection()

namespace pann
{
    class Net : public Object
    {
    public:
        enum NeuronRole { WorkNeuron = 0, InputNeuron = 1 };

    private:
        unsigned threadCount;
        unsigned lastNeuronId; //var to add new neurons
        unsigned lastWeightId; //var to add new weights
        unsigned biasId;
        std::map<unsigned, Neuron> neurons;
        std::map<unsigned, Weight> weights;
        std::list<NeuronIter> inputNeurons;  //Iterators to map<> neurons
        NetCache cache;

        friend class NetPublicWrapper;

    private:
        NeuronIter findNeuron(int _neuronId);
        void regenerateCache();
        void formatFront(std::vector<NeuronIter>& _raw);

        static void threadBase( Runner* _runner, NetCache* _cache, unsigned _cur_thread_no, boost::barrier* _barrier)
        {
            RunDirection dir = _runner->getDirection();

            unsigned layer;
            (dir == ForwardRun) ?  (layer = 0) : (layer = _cache->data.size() - 2);
            do {
                //Process current layer
                NetCache::ThreadTaskType* task = &_cache->data[layer][_cur_thread_no];
                for(unsigned i = 0; i < task->size(); ++i)
                    _runner->run( (*task)[i] );

                //Wait for other threads
                _barrier->wait();
            } while( (dir == ForwardRun && ++layer < _cache->data.size() - 1) || (dir == BackwardRun && layer-- > 0) );
            /*
             * A little comment.
             * Cache structure:
             * Layer1:   thread1_data, thread2_data, ...
             * Layer2:   thread1_data, thread2_data, ...
             * ...
             * LayerN-1: thread1_data, thread2_data, ...
             * LayerN:          <= last layer. ALWAYS empty! (see Net::regenerateCache())
             * cache.size() == N+1;
             * thread_data is vector of NeuronIter
             */
        };

    public:
        Net();
        Net(int _threads);
        ~Net();

        int getThreadCount();
        void setThreadCount(int _threads);

        unsigned getBiasId();

        int addNeuron(ActivationFunction::Base* _activationFunction);
        int addInputNeuron();
        void delNeuron(int _neuronId);

        void setNeuronRole(int _neuronId, NeuronRole _newRole);
        NeuronRole getNeuronRole(int _neuronId);

        void setNeuronOwner(int _neuron, int _owner);
        int getNeuronOwner(int _neuron);

        void addConnection(int _from, int _to, Float _weightValue = 1);
        void delConnection(int _from, int _to);

        std::vector<int> getInputMap();

        void setInput(const std::valarray<Float>& _input);
        std::map<int, Float> getOutput();
        void getOutput(std::valarray<Float>& _output);

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
                boost::progress_display show_progress( 20 + neurons.size() + 20 );

                ar & boost::serialization::base_object<Object>(*this);

                //Saving basic data
                ar & lastNeuronId;
                ar & lastWeightId;
                ar & threadCount;
                ar & biasId;
                ar & neurons;
                show_progress += 10;
                ar & weights;
                show_progress += 10;

                //Links already saved by 'ar & neurons', but field like 'to' - not
                for(std::map<unsigned, Neuron>::const_iterator iter = neurons.begin(); iter != neurons.end(); ++iter)
                {
                    unsigned size = iter->second.links.size();
                    ar & size;
                    BOOST_FOREACH( const Link& l, iter->second.links )
                    {
                        Link& link = const_cast<Link&>(l);
                        unsigned to = link.getToIter()->first;
                        unsigned w  = link.getWeightIter()->first;
                        unsigned dir= (unsigned)link.getDirection();
                        unsigned latency = (unsigned)link.getLatency();
                        ar & to;
                        ar & w;
                        ar & dir;
                        ar & latency;
                    }

                    show_progress += 1;
                }
                
                //Saving input neurons
                unsigned size;
                size = inputNeurons.size();
                ar & size;
                BOOST_FOREACH( NeuronIter iter, inputNeurons )
                {
                    unsigned id = iter->first;
                    ar & id;
                }
                show_progress += 10;

                //Saving cache
                unsigned layers = cache.data.size();
                ar & layers;
                for(unsigned l = 0; l < cache.data.size(); l++)
                {
                    for(unsigned t = 0; t < threadCount; t++)
                    {
                        unsigned size = cache.data[l][t].size();
                        ar & size;
                        BOOST_FOREACH( NeuronIter iter, cache.data[l][t] )
                        {
                            unsigned id = iter->first;
                            ar & id;
                        }
                    }
                }
                show_progress += 10;
            };

        template<class Archive>
            void load(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);

                //Restoring basic data
                ar & lastNeuronId;
                ar & lastWeightId;
                ar & threadCount;
                ar & biasId;
                ar & neurons;
                boost::progress_display show_progress(20 + neurons.size() + 20);
                show_progress += 10;
                ar & weights;
                show_progress += 10;
               
                //Loading links data, converting neuron ID's to iterators
                for(NeuronIter iter = neurons.begin(); iter != neurons.end(); ++iter)
                {
                    unsigned size;
                    ar & size;
                    for(unsigned i = 0; i < size; i++)
                    {
                        unsigned to, w, dir, latency;
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
                    show_progress += 1;
                }

                //Loading list of input neurons
                inputNeurons.clear(); //may be we loading saved net into existing net with neurons?
                unsigned size;
                ar & size; 
                for(unsigned i = 0; i < size; i++)
                {
                    unsigned id; ar & id;
                    NeuronIter iter = neurons.find(id);
                    inputNeurons.push_back(iter);
                    if(iter == neurons.end())
                        throw Exception::FilesystemError()<<"Net::load(): can't load Net object. "
                                                                "Archive possibly damaged\n";
                }
                show_progress += 10;

                //Loading cache
                cache.flush();
                unsigned layers;
                ar & layers;
                for(unsigned l = 0; l < layers; l++)
                {
                    cache.data.push_back(NetCache::FrontType()); //add new layer to cache
                    for(unsigned t = 0; t < threadCount; t++)
                    {
                        cache.data[l].push_back(NetCache::ThreadTaskType()); //add new thread task info to current layer
                        unsigned size;
                        ar & size;
                        for(unsigned n = 0; n < size; n++)
                        {
                            unsigned id;
                            ar & id;
                            NeuronIter iter = neurons.find(id);
                            cache.data[l][t].push_back(iter);
                            if(iter == neurons.end())
                                throw Exception::FilesystemError()<<"Net::load(): can't load Net object. "
                                                                        "Archive possibly damaged\n";
                        }
                    }
                }
                cache.fixed();
                show_progress += 10;
            };

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

}; //pann
#endif //NET_H

