
#ifndef PANN_ALGORITHMS_LMS_H_INCLUDED
#define PANN_ALGORITHMS_LMS_H_INCLUDED

#include "Core/Runner.h"
#include "Core/Net.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann {
    namespace attr
    {
        namespace lms
        {
            const Hash error                = 1001;
            const Hash local_gradient       = 1002;
            const Hash epoch                = 1003;
            const Hash annealing_tsc        = 1004;
            const Hash learning_rate        = 1005;
            const Hash learning_momentum    = 1006;
            const Hash last_dw              = 1007; //Link attribute
        }; //lms
    }; //atrr

    class LmsBackpropagationRunner : public Runner
    {
        SINGLETON_SKELETON(LmsBackpropagationRunner, Runner);

        virtual void run(Object const * net, NeuronPtr neuron) const;
    }; //LmsBackpropagationRunner
    REGISTER_SINGLETON_H(LmsBackpropagationRunner);

    void lms_init(NetPtr net);

}; //pann

#endif //PANN_ALGORITHMS_LMSRUNNER_H_INCLUDED

