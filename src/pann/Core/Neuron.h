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

using namespace std;

namespace pann
{
    class Weight;
    class Link;

    class OpenGlAttributes
    {
    public:
        OpenGlAttributes() : x(0), y(0), z(0), r(0), g(0), b(0) {};
        virtual ~OpenGlAttributes() {};

        signed int x, y, z;
        unsigned char r, g, b;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_NVP(x)
                & BOOST_SERIALIZATION_NVP(y)
                & BOOST_SERIALIZATION_NVP(z)
                & BOOST_SERIALIZATION_NVP(r)
                & BOOST_SERIALIZATION_NVP(g)
                & BOOST_SERIALIZATION_NVP(b);
            };
    }; //OpenGlAttributes

    ADD_PTR_TYPEDEF(OpenGlAttributes)

    class Neuron : public Object
    {
    public:
        Neuron() {};
        Neuron(WeightPtr _bias) : bias(_bias) {};
        virtual ~Neuron() {};

        void setInput(Float _value);
        Float getOutput() const;

        virtual void fire() = 0;
        virtual void learn() = 0;

        //Only for pann_viewer. TODO
        const std::list<Link>& getInConnections() const { return links_in; };

    private:
        void addInConnection(NeuronPtr _to, WeightPtr _weight);
        void addOutConnection(NeuronPtr _to, WeightPtr _weight);
        void delInConnection(NeuronPtr _to);
        void delOutConnection(NeuronPtr _to);

    public:
        OpenGlAttributesPtr ogl;

    protected:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links_out;
        std::list<Link> links_in;
        WeightPtr bias;

    private:
        //template<class Archive>
        //friend void Net::serialize(Archive & ar, const unsigned int version);
        friend class Net;

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Object)
                 & BOOST_SERIALIZATION_NVP(receptiveField)
                 & BOOST_SERIALIZATION_NVP(activationValue)
                 //@see Net::serialize()
                 //& BOOST_SERIALIZATION_NVP(links_out)
                 //& BOOST_SERIALIZATION_NVP(links_in)
                 & BOOST_SERIALIZATION_NVP(bias)
                 & BOOST_SERIALIZATION_NVP(ogl);
            };
    }; //Neuron

    /**
     * If Neuron is input neuron - construct it with Linear activation function
     * and call setInput
     * Call fire() to produce activationValue
     * It will automatically 'suck up' activation values from downstream neurons
     */
    class PyramidalNeuron : public Neuron
    {
    public:
        PyramidalNeuron() {};
        PyramidalNeuron(ActivationFunction::Base* _af) : activationFunction(_af) {};
        PyramidalNeuron(ActivationFunction::Base* _af, WeightPtr _bias) : activationFunction(_af) { bias = _bias; };
        virtual ~PyramidalNeuron() {};

        virtual void fire();
        virtual void learn();

    private:
        ActivationFunction::Base* activationFunction;

        /* Serialization */
    private:
        friend class boost::serialization::access;

        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<PyramidalNeuron, Neuron>(
                    static_cast<PyramidalNeuron*>(NULL),
                    static_cast<Neuron*>(NULL));

                if(typename Archive::is_loading())
                    ActivationFunction::boost_export();

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Neuron)
                 & BOOST_SERIALIZATION_NVP(activationFunction);
            };
    };

}; //pann

#endif //NEURON_H

