#ifndef PANN_CORE_NEURON_H_INCLUDED
#define PANN_CORE_NEURON_H_INCLUDED

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Link.h"
#include "ActivationFunction.h"
#include "Runner.h"

using std::list;

namespace pann
{
    class Neuron : public Object
    {
    public:
        Neuron(ActivationFunctionPtr _af, WeightPtr _bias, RunnerPtr _fireRunner, RunnerPtr _learnRunner)
            : activationFunction(_af), bias(_bias), fireRunner(_fireRunner), learnRunner(_learnRunner)
        {
            if(ForwardRun != fireRunner->getDirection())
                throw Exception()<<"Neuron::Neuron(): Wrong direction\n";
            //Learning may be in forward direction too, so we don't check _learnRunner direction

            if(bias) {
                bias->incUsageCount();
                bias->incUsageCount();
            }
        };
        virtual ~Neuron() {};

        void setInput(Float _value)     { receptiveField = _value; };
        Float getReceptiveField() const { return receptiveField; };
        Float getOutput() const         { return activationValue; };

        const list<Link>& getInConnections()  const { return links_in; };
        const list<Link>& getOutConnections() const { return links_out; };

        WeightPtr getBias() const                           { return bias; };
        ActivationFunctionPtr getActivationFunction() const { return activationFunction; };
        RunnerPtr getFireRunner() const                     { return fireRunner; };
        RunnerPtr getLearnRunner() const                    { return learnRunner; };


    private:
        //For pann::Net
        typedef struct {
            static bool comp(NeuronPtr _to, const Link& _l) {
                return _l.getTo() == _to;
            }
        } ComparatorT;

        void addInConnection(NeuronPtr _to, WeightPtr _weight)  { links_in.push_back( Link(_to, _weight) ); };
        void addOutConnection(NeuronPtr _to, WeightPtr _weight) { links_in.push_back( Link(_to, _weight) ); };
        void delInConnection(NeuronPtr _to)  { links_in.remove_if(bind(ComparatorT::comp, _to, _1)); };
        void delOutConnection(NeuronPtr _to) { links_out.remove_if(bind(ComparatorT::comp, _to, _1)); };

    public:
        Float receptiveField;
        Float activationValue;

    private:
        list<Link> links_out;
        list<Link> links_in;
        ActivationFunctionPtr activationFunction;
        WeightPtr bias;
        RunnerPtr fireRunner;
        RunnerPtr learnRunner;

    private:
        //friend template<class Archive> void Net::serialize(Archive & ar, const unsigned int version);
        friend class Net;

        Neuron() {};

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
    ADD_PTR_TYPEDEF(Neuron);

}; //pann

#endif //PANN_CORE_NEURON_H_INCLUDED

