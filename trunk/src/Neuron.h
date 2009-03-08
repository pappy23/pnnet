//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"
#include "Net.h"

namespace pann
{
    class Neuron : public Object
    {
    protected:
        ActivationFunction::Base& activationFunction;
        std::list<Link> links;
        int a_hops;
        int ownerThread;

        std::list<Link>::iterator findLink(Neuron& _to);

        void connect(Neuron& _to, float _weightValue);
        void connect(Neuron& _to, boost::shared_ptr<Weight> _weight);
        void disconnect(Neuron& _to);

        void setOwnerThread(int _thread);
        inline int getOwnerThread() { return ownerThread; };

    public:
        friend class Net;

        float receptiveField;
        float activationValue;

        Neuron();
        Neuron(ActivationFunction::Base&); 
        ~Neuron();
        
        float activate();
    };

}; //pann

#endif //NEURON_H

