#ifndef PANN_RUNNERS_PYRAMIDALNEURONFEEDFORWARDRUNNER_H_INCLUDED
#define PANN_RUNNERS_PYRAMIDALNEURONFEEDFORWARDRUNNER_H_INCLUDED

#include "Core/Runner.h"

namespace pann
{
    /**
     * Runner for pyramidal neurons feedforward propagation
     */
    class PyramidalNeuronFeedforwardRunner : public Runner
    {
        SINGLETON_SKELETON(PyramidalNeuronFeedforwardRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;
    }; //PyramidalNeuronFeedforwardRunner
    REGISTER_SINGLETON_H(PyramidalNeuronFeedforwardRunner);

}; //pann

#endif //PANN_RUNNERS_PYRAMIDALNEURONFEEDFORWARDRUNNER_H_INCLUDED

