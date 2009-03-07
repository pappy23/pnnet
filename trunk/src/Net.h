//Net.h

#ifndef NET_H
#define NET_H 

#include "Includes.h"
#include "Object.h"
#include "Weight.h"
#include "Neuron.h"

namespace pann
{

    class Net : public Object
    {
    protected:
        std::map<int, Neuron> neurons;
        int lastNeuronId;

    public:
        Net();
        ~Net();

        int addNeuron(ActivationFunction::Base&);
        Neuron& getNeuron(int);
        void delNeuron(int);
    };

}; //pann
#endif //NET_H

