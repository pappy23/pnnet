//Net.h

#ifndef NET_H
#define NET_H

#include "Includes.h"
#include "Object.h"
#include "Neuron.h"
#include "Cache.h"
#include "Runner.h"

//TODO: add shared weight function addConnection()

namespace pann
{
    class NetCache : public Cache
    {
        /* Public types */
    public:
        typedef std::vector<Neuron*> ThreadTaskType;
        typedef std::vector<ThreadTaskType> FrontType;

        /* Public members */
    public:
        std::vector<FrontType> data;

        /* Public interface */
    public:
        virtual void flush()
        {
            data.clear();
            touch();
        }

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(coherent);
                ar & BOOST_SERIALIZATION_NVP(data);
            };             
    };

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
         * TODO: get rid of this functions, set threadCount as parametr to run()
         * TODO: rewrite cache regeneration procedure to not rely on actual threadCount
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
        const std::map<unsigned, Neuron*>& getNeurons() const;

        /**
         * Get ID of bias neuron
         * Remark: bias neuron is implemented as work neuron, 
         * with self-recurrent connection (w=1), placed 
         * at first cache layer
         */
        unsigned getBiasId() const;

        /* Public members */
    public:
        LearningHint::Base* learningHint;

        /* Private members */
    private:
        unsigned threadCount;
        unsigned lastNeuronId; //var to add new neurons
        unsigned biasId;
        std::map<unsigned, Neuron*> neurons;
        std::list<Neuron*> inputNeurons;
        NetCache mutable cache;

        /* Private methods */
    private:
        /**
         * Returns Neuron* for corresponding neuron ID
         */
        Neuron* findNeuron(unsigned _neuronId);
        const Neuron* findNeuron(unsigned _neuronId) const;

        /**
         * Helper used by regenerateCache()
         */
        void formatFront(std::vector<Neuron*>& _raw) const;

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerateCache() const;

        /**
         * This function is executed by work thread, instantiated from run()
         */
        static void threadBase(Runner* _runner, NetCache* _cache, unsigned _cur_thread_no, boost::barrier* _barrier)
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
             * thread_data is vector of Neuron*
             */
        };

        /* Serialization */
    private:
        //TODO: check for memory leaks and doubling after serialization
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                //ar & boost::serialization::base_object<Object>(*this);
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(lastNeuronId)
                 & BOOST_SERIALIZATION_NVP(threadCount)
                 & BOOST_SERIALIZATION_NVP(biasId)
                 & BOOST_SERIALIZATION_NVP(neurons)
                 & BOOST_SERIALIZATION_NVP(inputNeurons)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(learningHint);
            };
    };

}; //pann
#endif //NET_H

