//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Object.h"

namespace pann
{

    class Neuron : public Object
    {
    public:
        Neuron(int);
        ~Neuron();
    };

}; //pann

#endif //NEURON_H

