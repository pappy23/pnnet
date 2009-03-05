//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron : public Object
    {
    public:
        Neuron(ActivationFunction::Base & activationFunction) : 
            activationFunction(activationFunction), 
            receptiveField(0), 
            activationValue(activationFunction.f(0)) { };

        ~Neuron() { };
        
        ActivationFunction::Base & activationFunction;
        float receptiveField;
        float activationValue;
        std::vector<Link> links;
    };

}; //pann

#endif //NEURON_H

