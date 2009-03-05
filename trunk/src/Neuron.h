//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Object.h"

namespace pann
{

    class Neuron : public Object
    {
    public:
        Neuron::Neuron(ActivationFunction::Base & activationFunction) : 
            this->activationFunction(activationFunction), 
            this->receptiveField(0), 
            this->activationValue(activationFunction::f(0)) { };

        ~Neuron() { };
        
        ActivationFunction::Base & activationFunction;
        float receptiveField;
        float activationValue;
        vector<Link> links;
    };

}; //pann

#endif //NEURON_H

