//Net.h

#ifndef NET_H
#define NET_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Exception.h"
#include "NetCache.h"

//TODO: documentation is not up to date

namespace pann
{
    class Neuron;
    class Weight;
    class Runner;

    class Net : public Object
    {
        /* Attributes */
    public:
        static const AttributeName workThreads;
        /* Public interface */
    public:
        /**
         * Default constructor. 
         * Creates empty net and sets threadCount to 
         * hardware specific number (depends on available processors)
         * Although creates bias neuron
         */
        Net() throw();
        virtual ~Net() throw();

        /**
         * Manipulate neurons in network
         */
        void addInputNeuron(Neuron*) throw();
        void removeNeuron(Neuron* _neuron) throw();

        /**
         * Manage connections between neurons
         * TODO: add connections with different latencies (shortcut links)
         */
        Weight* addConnection(Neuron* _from, Neuron* _to, Weight* _weight = 0) throw();
        void delConnection(Neuron* _from, Neuron* _to) throw(E<Exception::Unbelievable>);

        /**
         * Add values to input neurons receptive fields
         */
        void setInput(const std::valarray<Float>& _input) throw(E<Exception::SizeMismatch>);

        /**
         * Assign neurons outputs to specified by @param _output valarray
         * (it is slower then above version, but more useful)
         */
        void getOutput(std::valarray<Float>& _output) const throw();

        /**
         * Apply @param _runner Runner to each neuron,
         * layer by layer
         * Note: layers are computed automaticaly and stored in cache
         * See regenerateCache() implementation for more details
         */
        void run(Runner& _runner, unsigned _threads = 0) throw();

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& getCache() const throw();

        /* Private members */
    private:
        std::list<Neuron*> inputNeurons;
        NetCache mutable cache;

        /* Private methods */
    private:
        /**
         * Helper used by regenerateCache()
         */
        void formatFront(std::vector<Neuron*>& _raw) const throw();

        /**
         * This function updates cache
         * Be extremely careful!
         */
        void regenerateCache() const throw(E<Exception::Unbelievable>);

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
                 & BOOST_SERIALIZATION_NVP(cache);
            };
    };

}; //pann
#endif //NET_H

