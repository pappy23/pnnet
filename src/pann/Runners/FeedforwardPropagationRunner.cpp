//FeedforwardPropagationRunner.cpp

#include "FeedforwardPropagationRunner.h"

REGISTER_SINGLETON_CPP(FeedforwardPropagationRunner);

#include "Core/Neuron.h"

namespace pann {

    void
    FeedforwardPropagationRunner::run(NeuronPtr _neuron, Net* _net) const
    {
        const RunnerPtr& r = _neuron->getFireRunner();

        if(r && r->getDirection() == ForwardRun)
        {
            r->run(_neuron, _net);
        } else {
            throw Exception()<<"Wrong runner\n";
        }
    } //run

}; //pann
