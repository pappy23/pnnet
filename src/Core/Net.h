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
        /* Public types */
    public:
        enum NeuronRole { WorkNeuron = 0, InputNeuron = 1 };

        /* Public interface */
    public:
        /**
         * Default constructor. 
         * Creates empty net and sets threadCount to 
         * hardware specific number (depends on available processors)
         * Although creates bias neuron
         */
        Net();

        /**
         * Same as above, but threadCount is set to @param _threads
         */
        Net(unsigned _threads);
        ~Net();

        /**
         * Manipulate threadCount
         */
        unsigned getThreadCount() const;
        void setThreadCount(unsigned _threads);

        /**
         * Manipulate neurons in network
         * Remark: addInputNeuron adds neuron with
         * ActivationFunction::Linear
         */
        unsigned addNeuron(ActivationFunction::Base* _activationFunction);
        unsigned addInputNeuron();
        void delNeuron(unsigned _neuronId);

        /**
         * Can turn work neuron to be input and vice versa
         */
        void setNeuronRole(unsigned _neuronId, NeuronRole _newRole);
        NeuronRole getNeuronRole(unsigned _neuronId) const;

        /**
         * Manage connections between neurons
         * TODO: add shared connections for convolution networks
         */
        void addConnection(unsigned _from, unsigned _to, Float _weightValue = 1);
        void delConnection(unsigned _from, unsigned _to);

        /**
         * Manage neuron owner thread
         * It is usually much higher then threadCount
         */
        void setNeuronOwner(unsigned _neuron, unsigned _owner);
        unsigned getNeuronOwner(unsigned _neuron) const;

        /**
         * Return IDs of input neurons
         * (use it in case you don't "remember" what neurons are input or their order)
         */
        std::vector<unsigned> getInputMap() const;

        /**
         * Add values to input neurons receptive fields
         */
        void setInput(const std::valarray<Float>& _input);

        /**
         * Returns pairs<input_neuron_id, it's output>
         * (only for neurons in last cache layer)
         */
        std::map<unsigned, Float> getOutput() const;

        /**
         * Assign neurons outputs to specified by @param _output valarray
         * (it is slower then above version, but more useful)
         */
        void getOutput(std::valarray<Float>& _output) const;

        /**
         * Apply @param _runner Runner to each neuron,
         * layer by layer
         * Note: layers are computed automaticaly and stored in cache
         * See regenerateCache() implementation for more details
         */
        void run(Runner* _runner);

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& getCache() const;
        const std::map<unsigned, Neuron>& getNeurons() const;
        const std::map<unsigned, Weight>& getWeights() const;

        /**
         * Get ID of bias neuron
         * Remark: bias neuron is implemented as work neuron, 
         * with self-recurrent connection (w=1), placed 
         * at first cache layer
         */
        unsigned getBiasId() const;

        /* Private members */
    private:
        unsigned threadCount;
        unsigned lastNeuronId; //var to add new neurons
        unsigned lastWeightId; //var to add new weights
        unsigned biasId;
        std::map<unsigned, Neuron> neurons;
        std::map<unsigned, Weight> weights;
        std::list<NeuronIter> inputNeurons;  //Iterators to map<> neurons
        NetCache mutable cache;

        /* Private methods */
    private:
        /**
         * Returns NeuronIterator for corresponding neuron ID
         */
        NeuronIter findNeuron(unsigned _neuronId);

        /**
         * Helper used by regenerateCache()
         */
        void formatFront(std::vector<NeuronIter>& _raw);

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerateCache();

        /**
         * This function is executed by work thread, instantiated from run()
         */
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

        /* Debug interface */
    public:
        void printDebugInfo(std::ostringstream& ost) const
        {
            
            ost<<"Net\n";
            ost<<" threadsCount: "<<threadCount<<std::endl;
            ost<<" lastNeuronId: "<<lastNeuronId<<std::endl;
            ost<<" lastWeightId: "<<lastWeightId<<std::endl;
            ost<<" neurons: ";
            ConstNeuronIter it = neurons.begin();
            for(; it != neurons.end(); ++it)
                ost<<it->first<<" ";
            ost<<"\n weights: ";
            ConstWeightIter wit = weights.begin();
            for(; wit != weights.end(); ++wit)
                ost<<wit->first<<" ";
            ost<<"\n inputNeurons: ";
            std::list<NeuronIter>::const_iterator it2 = inputNeurons.begin();
            for(; it2 != inputNeurons.end(); ++it2)
                ost<<(*it2)->first<<" ";
            ost<<"\n\n neurons: ";
            for(it = neurons.begin(); it != neurons.end(); ++it)
                it->second.printDebugInfo(ost);
            
            ost<<"\n\n Cache:\n";
            cache.printDebugInfo(ost);
        };

        /* Serialization */
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

