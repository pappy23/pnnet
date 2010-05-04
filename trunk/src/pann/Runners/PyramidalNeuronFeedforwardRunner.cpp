//PyramidalNeuronFeedforwardRunner.cpp

#include "PyramidalNeuronFeedforwardRunner.h"

REGISTER_SINGLETON_CPP(PyramidalNeuronFeedforwardRunner);

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/ActivationFunction.h"

namespace pann {
    void
    PyramidalNeuronFeedforwardRunner::run(NeuronPtr _neuron, Net* _net) const
    {
        if(_neuron->getActivationFunction())
        {
            if(_neuron->getBias())
                _neuron->receptiveField += _neuron->getBias()->getValue();

            BOOST_FOREACH( const Link& link, _neuron->getInConnections() )
                _neuron->receptiveField += link.getTo()->getOutput() * link.getWeight()->getValue();

            _neuron->activationValue = _neuron->getActivationFunction()->f(_neuron->receptiveField);
        }

        _neuron->receptiveField = 0;
    } //run

}; //pann

