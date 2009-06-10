//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Link.h"
#include "ActivationFunction.h"

using std::list;

namespace pann
{
    class Weight;
    class Link;

    class Neuron : public Object
    {
        Neuron() {};

    public:
        virtual ~Neuron() {};

        //TODO
        list<Link>& getInConnections() { return links_in; };
        list<Link>& getOutConnections() { return links_out; };

        //TODO
        void setInput(Float _value) { receptiveField = _value; };
        Float getOutput() const { return activationValue; };
        const WeightPtr& getBias() { return bias; };
        const ActivationFunctionPtr& getActivationFunction() { return activationFunction; };

        const WeightPtr& getBias() const { return bias; };
        const RunnerPtr& getFireRunner() const { return fireRunner; };
        const RunnerPtr& getLearnRunner() const { return learnRunner; };
        //TODO setRunner(), check fro direction

    private:
        void addInConnection(NeuronPtr _to, WeightPtr _weight);
        void addOutConnection(NeuronPtr _to, WeightPtr _weight);
        void delInConnection(NeuronPtr _to);
        void delOutConnection(NeuronPtr _to);

        list<Link> links_out;
        list<Link> links_in;

    public: //TODO
        Float receptiveField;
        Float activationValue;

    private:
        WeightPtr bias;
        ActivationFunctionPtr activationFunction;
        RunnerPtr fireRunner;
        RunnerPtr learnRunner;

    private:
        //template<class Archive>
        //friend void Net::serialize(Archive & ar, const unsigned int version);
        friend class Net;
        friend class NeuronFactory;

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

