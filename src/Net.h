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

        Neuron& findNeuron(int _neuronId);

    public:
        Net();
        ~Net();

        int addNeuron(ActivationFunction::Base& _activationFunction);
        void delNeuron(int _neuronId);
        void addConnection(int _from, int _to, float _weightValue = 1);
        void delConnection(int _from, int _to);
    };

}; //pann
#endif //NET_H

