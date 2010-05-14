
#ifndef PANN_ALGORITHMS_LMS_H_INCLUDED
#define PANN_ALGORITHMS_LMS_H_INCLUDED

#include "Core/Runner.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann {
    class LmsBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(LmsBackpropagationRunner, Runner);

        virtual void run(ObjectConstPtr net, NeuronPtr neuron) const;
    }; //LmsBackpropagationRunner
    REGISTER_SINGLETON_H(LmsBackpropagationRunner);
}; //pann

#endif //PANN_ALGORITHMS_LMSRUNNER_H_INCLUDED

