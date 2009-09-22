//PyramidalNeuronFeedforwardRunner.h

#ifndef PYRAMIDALNEURONFEEDFORWARDRUNNER_H
#define PYRAMIDALNEURONFEEDFORWARDRUNNER_H

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

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    }; //PyramidalNeuronFeedforwardRunner
    REGISTER_SINGLETON_H(PyramidalNeuronFeedforwardRunner);

}; //pann

#endif
