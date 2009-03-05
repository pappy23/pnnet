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
    public:
        ActivationFunction::Base & activationFunction;
        float receptiveField;
        float activationValue;
        std::vector<Link> links;

        Neuron(ActivationFunction::Base & activationFunction) : 
            activationFunction(activationFunction), 
            receptiveField(0), 
            activationValue(activationFunction.f(0)) { };

        ~Neuron() { };

        int connectTo(Neuron & to, Weight & w)
        {
            //if(links.find(link with to == to))
            //    throw E("Achtung!");
            Link link_to(to, w, Link::Direction::out);
            links.push_back(link_to);

            Link link_from(*this, w, Link::Direction::in);
            to.links.push_back(link_from);

            return 0;
        };

        int connectFrom(Neuron & from, Weight & w)
        {
            return from.connectTo(*this, w);
        };
    };

}; //pann

#endif //NEURON_H

