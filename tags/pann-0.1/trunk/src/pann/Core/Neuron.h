//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"
#include "Includes/BoostSerialization.h"

#include "Object.h"
#include "Exception.h"
#include "ActivationFunction.h"
#include "Weight.h"
#include "Link.h"

namespace pann
{
    class Weight;
    class Link;

    /**
     * If Neuron is input neuron - construct it with Linear activation function
     * and call setInput
     * Call fire() to produce activationValue
     * It will automatically 'suck up' activation values from downstream neurons
     */
    class Neuron : public Object
    {
    public:
        Neuron(ActivationFunction::Base*, WeightPtr _bias = WeightPtr((Weight*)0));
        virtual ~Neuron();

        Float getReceptiveField() const;
        Float getActivationValue() const;
        void setInput(Float _value);

        const ActivationFunction::Base& getActivationFunction() const;

        void addInConnection(NeuronPtr _to, WeightPtr _weight);
        void addOutConnection(NeuronPtr _to, WeightPtr _weight);
        void delInConnection(NeuronPtr _to);
        void delOutConnection(NeuronPtr _to);

        const std::list<Link>& getInConnections() const;
        const std::list<Link>& getOutConnections() const;

        bool hasBias() const;
        WeightPtr getBias();
        const WeightPtr getBias() const;

        virtual void fire();

    private:
        Float receptiveField;
        Float activationValue;
        ActivationFunction::Base* activationFunction;
        std::list<Link> links_out;
        std::list<Link> links_in;
        WeightPtr bias;

        /* Serialization */
    private:
        Neuron() { };
        friend class boost::serialization::access;

        //template<class Archive>
        //friend void Net::serialize(Archive & ar, const unsigned int version);
        friend class Net;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ActivationFunction::boost_export();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(receptiveField)
                 & BOOST_SERIALIZATION_NVP(activationValue)
                 & BOOST_SERIALIZATION_NVP(activationFunction)
                 //Let Net do serialization
                 //& BOOST_SERIALIZATION_NVP(links_out)
                 //& BOOST_SERIALIZATION_NVP(links_in)
                 & BOOST_SERIALIZATION_NVP(bias);
            };
    };

}; //pann

#endif //NEURON_H
