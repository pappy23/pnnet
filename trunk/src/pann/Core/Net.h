//Net.h

#ifndef NET_H
#define NET_H

#include "Includes.h"
#include "Object.h"
#include "Attributes.h"
#include "Neuron.h"
#include "NetCache.h"
#include "Runner.h"

//TODO: add shared weight function addConnection()
//TODO: documentation is not up to date

namespace pann
{
    class Net : public Object
    {
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
         * Remark: addInputNeuron adds neuron with
         * ActivationFunction::Linear
         */
        unsigned addNeuron(ActivationFunction::Base* _activationFunction) throw(E<Exception::ElementExists>);
        unsigned addInputNeuron() throw();
        void delNeuron(unsigned _neuronId) throw();

        /**
         * Manage connections between neurons
         * TODO: add shared connections for convolution networks
         * TODO: add connections with different latencies (shortcut links)
         */
        void addConnection(unsigned _from, unsigned _to, Float _weightValue = 1) throw();
        void delConnection(unsigned _from, unsigned _to) throw();

        /**
         * Add values to input neurons receptive fields
         */
        void setInput(const std::valarray<Float>& _input) throw(E<Exception::SizeMismatch>);
        void setInput(unsigned _neuronId, Float _value) throw();

        /**
         * Assign neurons outputs to specified by @param _output valarray
         * (it is slower then above version, but more useful)
         */
        void getOutput(std::valarray<Float>& _output) const throw();
        Float getOutput(unsigned _neuronId) const throw();

        /**
         * Apply @param _runner Runner to each neuron,
         * layer by layer
         * Note: layers are computed automaticaly and stored in cache
         * See regenerateCache() implementation for more details
         */
        void run(Runner* _runner, unsigned _threads = 0) throw();

        /**
         * Public interface to private attributes
         * (they are used while training or painting net in pann_viewer)
         */
        const NetCache& getCache() const throw();

        /**
         * Get ID of bias neuron
         * Remark: bias neuron is implemented as work neuron, 
         * with self-recurrent connection (w=1), placed 
         * at first cache layer
         */
        unsigned getBiasId() const throw();

        /* Public members */
    public:
        Attributes learningHint;

        /* Private members */
    private:
        unsigned lastNeuronId; //var to add new neurons
        std::map<unsigned, Neuron*> neurons;
        std::list<Neuron*> inputNeurons;
        unsigned biasId;
        NetCache mutable cache;

        /* Private methods */
    private:
        /**
         * Returns Neuron* for corresponding neuron ID
         */
        Neuron* findNeuron(unsigned _neuronId) throw(E<Exception::ObjectNotFound>);
        const Neuron* findNeuron(unsigned _neuronId) const throw();
        std::map<unsigned, const Neuron*> getOutputNeurons() const throw();

        /**
         * Real net modificators
         */
        void addConnection(Neuron* _from, Neuron* _to, Weight* _weight) throw();
        void delConnection(Neuron* _from, Neuron* _to) throw(E<Exception::Unbelievable>);

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
                 & BOOST_SERIALIZATION_NVP(lastNeuronId)
                 & BOOST_SERIALIZATION_NVP(biasId)
                 & BOOST_SERIALIZATION_NVP(neurons)
                 & BOOST_SERIALIZATION_NVP(inputNeurons)
                 & BOOST_SERIALIZATION_NVP(cache)
                 & BOOST_SERIALIZATION_NVP(learningHint);
            };
    };

}; //pann
#endif //NET_H

