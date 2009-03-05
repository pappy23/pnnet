//Net.h

#ifndef NET_H
#define NET_H 

#include "Includes.h"
#include "ActivationFunction.h"
#include "Object.h"
#include "Weight.h"
#include "Neuron.h"

namespace pann
{

    class Net : public Object
    {
    public:
        Net() { };
        ~Net() { };

        std::map<std::string, const ActivationFunction::Base &> activationFunctions;
        std::vector<Neuron> neurons;
        std::vector<Weight> weights;
        //WTF?!
        //std::vector<Neuron &> inputNeurons; 
        //std::vector<Neuron &> outputNeurons;
    };

}; //pann
#endif //NET_H

