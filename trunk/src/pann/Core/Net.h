#ifndef PANN_CORE_NET_H
#define PANN_CORE_NET_H

#include "Includes/Std.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Exception.h"
#include "NetCache.h"
#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

namespace pann
{
    class Net : public Object //, public boost::enable_shared_from_this<Net>
    {
    public:
        enum RunDirection { ForwardRun, BackwardRun };

    public:
        /**
         * Default constructor
         * Creates empty net and sets threadCount to
         * hardware specific number (depends on available processors)
         */
        Net();
        virtual ~Net();

        /**
         * Manipulate neurons in network
         */
        void add_input_neuron(NeuronPtr);
        //TODO Fix removal of neurons and connections.
        //We can stuck with hanging part of topology
        void remove_neuron(NeuronPtr);

        /**
         * Manage connections between neurons
         * TODO: add connections with different latencies (shortcut links)
         */
        WeightPtr add_connection(
                NeuronPtr from,
                NeuronPtr to,
                WeightPtr weight = WeightPtr((Weight*)0));
        void remove_connection(NeuronPtr from, NeuronPtr to);

        /**
         * Add values to input neurons receptive fields
         */
        void set_input(const std::valarray<Float>& input);

        /**
         * Assign neurons outputs to specified by @param _output valarray
         * (it is slower then above version, but more useful)
         */
        void get_output(std::valarray<Float>& output) const;

        /**
         * Apply @param _runner Runner to each neuron,
         * layer by layer
         * Note: layers are computed automaticaly and stored in cache
         * See regenerateCache() implementation for more details
         */
        void run(RunDirection direction, RunnerPtr runner);

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& get_cache() const;

        /**
         * Manipulate count of work threads
         */
        unsigned get_work_threads_count() const;
        void set_work_threads_count(unsigned count);

    private:
        std::list<NeuronPtr> input_neurons;
        NetCache mutable cache;
        unsigned work_threads_count;

        /**
         * Helper used by regenerateCache()
         */
        void format_front(std::list<NeuronPtr>& raw) const;

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerate_cache() const;

        /**
         * This function is executed by work thread, instantiated from run()
         * @param _runner Runner to apply
         * @param _net Net context, used for access to global net attributes
         * @param _cur_thread Current work thread number
         * @param _barrier See implementation
         */
        static void thread_base(RunDirection dir, RunnerPtr runner, Net *net, unsigned cur_thread, boost::barrier *barrier);

        /* Serialization */
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                using namespace boost::serialization;

                //It's for manual serialization of Neuron connections
                if(typename Archive::is_saving() && !cache.is_ok())
                    regenerate_cache();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(input_neurons)
                 & BOOST_SERIALIZATION_NVP(work_threads_count);

                //Serialize Neuron connections
                for(unsigned i = 0; i < cache.layers.size(); ++i)
                    for(unsigned j = 0; j < cache.layers[i].size(); ++j)
                    {
                        ar & make_nvp("input_links", cache.layers[i][j]->input_links);
                        ar & make_nvp("output_links", cache.layers[i][j]->output_links);
                    }
            };
    };

}; //pann
#endif //NET_H

