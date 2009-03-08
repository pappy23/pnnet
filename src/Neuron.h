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

        std::list<Link>::iterator findLink(Neuron& _to);

        void connect(Neuron& _to, float _weightValue);
        void connect(Neuron& _to, Weight* _weight);
        void disconnect(Neuron& _to);

    public:
        friend class Net;

        float receptiveField;
        float activationValue;

        Neuron(ActivationFunction::Base&); 
        ~Neuron();
        
        float activate();
    };

}; //pann

#endif //NEURON_H

