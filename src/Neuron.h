//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron;

    //typedef std::map<int, Neuron>::iterator NeuronIter;

    class Neuron : public Object
    {
    protected:
        //VARS

        ActivationFunction::Base& activationFunction;

        //List of Links, both directions
        std::list<Link> links;
        
        //Thread with this number will take care of our Neuron
        int ownerThread;

        //METHODS

        //Helper. Finds returns iterator to list<> links for Neuron& _to
        std::list<Link>::iterator findLink(NeuronIter _to, Link::Direction _direction);

        //Add link to *this neuron
        //Create new Weight object
        void connect(NeuronIter _to, Link::Direction _direction, float _weightValue);

        //Use existing Weight
        void connect(NeuronIter _to, Link::Direction _direction, boost::shared_ptr<Weight> _weight);
        
        //Destroy connection
        void disconnect(NeuronIter _to, Link::Direction _direction);

        //Get/set ownerThread
        //with bound checking
        void setOwnerThread(int _thread);
        inline int getOwnerThread() { return ownerThread; };

    public:
        friend class Net;

        float receptiveField;
        float activationValue;

        Neuron();
        Neuron(ActivationFunction::Base&); 
        ~Neuron();
        
        //Calculate activationValue from receptiveField
        float activate();
    };

}; //pann

#endif //NEURON_H

