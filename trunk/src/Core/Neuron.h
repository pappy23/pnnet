//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron : public Object
    {
    protected:
        //VARS

        ActivationFunction::Base& activationFunction;

        //Thread with this number will take care of our Neuron
        int ownerThread;

        //METHODS

        //Helper. Finds and returns iterator to list<> links for Neuron& _to
        std::list<Link>::iterator findLink(NeuronIter _to, Link::Direction _direction);

    public:
        Float activationValue;

        std::list<Link> links;//!< List of Link, both directions

        Float receptiveField;

        //! Deafult constructor with Line acitvation function and 0 in all other parametrs
        Neuron();

        Neuron(ActivationFunction::Base&);

        ~Neuron();

        //! Add link to *this neuron
        //! Create new Weight object
        void connect(NeuronIter _to, Link::Direction _direction, Float _weightValue);

        //! Use existing Weight
        void connect(NeuronIter _to, Link::Direction _direction, boost::shared_ptr<Weight> _weight);

        //! Destroy connection
        void disconnect(NeuronIter _to, Link::Direction _direction);

        //! Set ownerThread, with bound checking
        void setOwnerThread(int _thread);

        //! Get ownerThread, with bound checking
        inline int getOwnerThread() { return ownerThread; };

        void printDebugInfo(std::ostringstream& ost);

        //! Calculate activationValue from receptiveField
        void activate();

        Float getActivationValue();

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);
                ar & activationFunction;
                ar & ownerThread;
                ar & activationValue;
                ar & receptiveField;
                ar & links;
            };
    };

}; //pann

#endif //NEURON_H

