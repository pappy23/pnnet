//Net.h

#ifndef NET_H
#define NET_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Exception.h"
#include "NetCache.h"
#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

namespace pann
{
//    class Neuron;
    class Weight;
    class Runner;

    class Net : public Object
    {
    public:
        /**
         * Default constructor
         * Creates empty net and sets threadCount to
         * hardware specific number (depends on available processors)
         * Although creates bias neuron
         */
        Net();
        virtual ~Net();

        /**
         * Manipulate neurons in network
         */
        void addInputNeuron(NeuronPtr);
        //TODO Fix removal of neurons and connections.
        //We can stuck with hanging part of topology
        void removeNeuron(NeuronPtr);

        /**
         * Manage connections between neurons
         * TODO: add connections with different latencies (shortcut links)
         */
        WeightPtr addConnection(
                NeuronPtr _from,
                NeuronPtr _to,
                WeightPtr _weight = WeightPtr((Weight*)0));
        void delConnection(NeuronPtr _from, NeuronPtr _to);

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
        void run(RunnerPtr _runner);

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

    private:
        std::list<NeuronPtr> inputNeurons;
        NetCache mutable cache;
        unsigned workThreads;

        /**
         * Helper used by regenerateCache()
         */
        void formatFront(std::list<NeuronPtr>& _raw) const;

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerateCache() const;

        /**
         * This function is executed by work thread, instantiated from run()
         * @param _runner Runner to apply
         * @param _net Net context, used for access to global net attributes
         * @param _cur_thread Current work thread number
         * @param _barrier See implementation
         */
        static void threadBase(RunnerPtr _runner, Net* _net, unsigned _cur_thread, boost::barrier* _barrier);
        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                using namespace boost::serialization;

                //It's for manual serialization of Neuron connections
                if(typename Archive::is_saving() && !cache.isOk())
                    regenerateCache();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(inputNeurons)
                 & BOOST_SERIALIZATION_NVP(workThreads);

                //Serialize Neuron connections
                for(unsigned i = 0; i < cache.layers.size(); ++i)
                    for(unsigned j = 0; j < cache.layers[i].size(); ++j)
                    {
                        ar & make_nvp("links_out", cache.layers[i][j]->links_out);
                        ar & make_nvp("links_in", cache.layers[i][j]->links_in);
                    }
            };
    };

}; //pann
#endif //NET_H

