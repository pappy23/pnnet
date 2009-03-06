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
        ActivationFunction::Base& _activationFunction;
        std::list<Link> _links;

    public:
        float receptiveField;
        float activationValue;

        Neuron(ActivationFunction::Base& activationFunction); 
        ~Neuron();
        
        void connectTo(Neuron&, Link::Direction, float);
        void connectTo(Neuron&, Weight*, Link::Direction);

        float activate();
    };

}; //pann

#endif //NEURON_H

