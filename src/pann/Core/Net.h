//Net.h

#ifndef NET_H
#define NET_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Exception.h"
#include "NetCache.h"
#include "Weight.h"

using boost::shared_ptr;

namespace pann
{
    class Neuron;
    class Weight;
    class Runner;

    class Net : public Object
    {
    public:
        /**
         * Default constructor. 
         * Creates empty net and sets threadCount to 
         * hardware specific number (depends on available processors)
         * Although creates bias neuron
         */
        Net();
        virtual ~Net();

        /**
         * Manipulate neurons in network
         */
        void addInputNeuron(shared_ptr<Neuron>);
        //TODO Fix removal of neurons and connection. We may get memory leaks and/or stuck with hanging topology part
        void removeNeuron(shared_ptr<Neuron>);

        /**
         * Manage connections between neurons
         * TODO: add connections with different latencies (shortcut links)
         */
        shared_ptr<Weight> addConnection(
                shared_ptr<Neuron> _from, 
                shared_ptr<Neuron> _to, 
                shared_ptr<Weight> _weight = shared_ptr<Weight>((Weight*)0));
        void delConnection(shared_ptr<Neuron> _from, shared_ptr<Neuron> _to);

        /**
         * Add values to input neurons receptive fields
         */
        void setInput(const std::valarray<Float>& _input);

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
        void run(Runner& _runner);

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& getCache() const;

        /**
         * Manipulate count of work threads
         */
        unsigned getWorkThreadsCount() const;
        void setWorkThreadsCount(unsigned _count);

        /* Private members */
    private:
        std::list<shared_ptr<Neuron> > inputNeurons;
        NetCache mutable cache;
        unsigned workThreads;

        /* Private methods */
    private:
        /**
         * Helper used by regenerateCache()
         */
        void formatFront(std::vector<shared_ptr<Neuron> >& _raw) const;

        /**
         * This function updates cache
         * Be extremely careful!
         */
        //TODO: Support Hopfield network, automatic shortcut detection
        void regenerateCache() const;

        /**
         * This function is executed by work thread, instantiated from run()
         */
        static void threadBase(Runner* _runner, const Net* _net, unsigned _cur_thread,
                                                                 unsigned _threads,
                                                                 boost::barrier* _barrier);

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(inputNeurons)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(workThreads);
            };
    };

}; //pann
#endif //NET_H

