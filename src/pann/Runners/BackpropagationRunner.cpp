//BackpropagationRunner.cpp

#include "BackpropagationRunner.h"

REGISTER_SINGLETON_CPP(BackpropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    BackpropagationRunner::run(NeuronPtr _neuron, Net* _net) const
    {
        const RunnerPtr& r = _neuron->getFireRunner();

        if(r && r->getDirection() == BackwardRun)
        {
            r->run(_neuron, _net);
        } else {
            throw Exception()<<"Wrong runner\n";
        }
    } //run

}; //pann

