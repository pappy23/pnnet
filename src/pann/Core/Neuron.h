//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Link.h"
#include "ActivationFunction.h"
#include "NeuronFactory.h"

using std::list;

namespace pann
{
    //TODO TODO TODO CONST PTRS!!! In Neuron, Net and Link methods

    class Weight;
    class Link;

    class Neuron : public Object
    {
        Neuron() {};

    public:
        virtual ~Neuron() {};

        void setInput(Float _value);
        Float getReceptiveField() const;
        Float getOutput() const;

        //TODO Hide this
        list<Link>& getInConnections();
        list<Link>& getOutConnections();

        //TODO ConstPtr
        const WeightPtr& getBias() const;
        const ActivationFunctionPtr& getActivationFunction();
        const RunnerPtr& getFireRunner() const;
        const RunnerPtr& getLearnRunner() const;


    private:
        //For pann::Net
        void addInConnection(NeuronPtr _to, WeightPtr _weight);
        void addOutConnection(NeuronPtr _to, WeightPtr _weight);
        void delInConnection(NeuronPtr _to);
        void delOutConnection(NeuronPtr _to);

        //For pann::NeuronFactory
        void setBias(WeightPtr _bias);
        void setActivationFunction(ActivationFunctionPtr _af);
        void setFireRunner(RunnerPtr _runner);
        void setLearnRunner(RunnerPtr _runner);

    public:
        Float receptiveField;
        Float activationValue;

    private:
        list<Link> links_out;
        list<Link> links_in;
        WeightPtr bias;
        ActivationFunctionPtr activationFunction;
        RunnerPtr fireRunner;
        RunnerPtr learnRunner;

    private:
        //template<class Archive>
        //friend void Net::serialize(Archive & ar, const unsigned int version);
        friend class Net;
        friend NeuronPtr NeuronFactory::CustomNeuron(ActivationFunctionPtr, WeightPtr, RunnerPtr, RunnerPtr);

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 //@see Net::serialize()
                 //& BOOST_SERIALIZATION_NVP(links_out)
                 //& BOOST_SERIALIZATION_NVP(links_in)
                 & BOOST_SERIALIZATION_NVP(receptiveField)
                 & BOOST_SERIALIZATION_NVP(activationValue)
                 & BOOST_SERIALIZATION_NVP(bias)
                 & BOOST_SERIALIZATION_NVP(activationFunction)
                 & BOOST_SERIALIZATION_NVP(fireRunner)
                 & BOOST_SERIALIZATION_NVP(learnRunner);
            };
    }; //Neuron

    //TODO template Neuron
    /*
    template<class FireRunner, class LearnRunner, class ActivationFunction>
        class Neuron : public Neuron
    {
    };
    */

}; //pann

#endif //NEURON_H

