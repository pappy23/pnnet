
#ifndef PANN_RUNNERS_LMSRUNNER_H_INCLUED
#define PANN_RUNNERS_LMSRUNNER_H_INCLUED

#include "Core/Exception.h"
#include "Core/Runner.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann {
    class LmsBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(LmsBackpropagationRunner, Runner);

        virtual void run(ObjectPtr net, NeuronPtr neuron) const;
    }; //LmsBackpropagationRunner
    REGISTER_SINGLETON_H(LmsBackpropagationRunner);
}; //pann

#endif //PANN_RUNNERS_LMSRUNNER_H_INCLUED

