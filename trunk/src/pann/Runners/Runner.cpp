//Runner.cpp

#include "Includes/BoostSerialization.h"
#include "Runner.h"

REGISTER_SINGLETON_CPP(NullFeedforwardRunner);
REGISTER_SINGLETON_CPP(NullBackpropagationRunner);
REGISTER_SINGLETON_CPP(FeedforwardPropagationRunner);
REGISTER_SINGLETON_CPP(BackpropagationRunner);

#include "Neuron.h"

namespace pann
{
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

