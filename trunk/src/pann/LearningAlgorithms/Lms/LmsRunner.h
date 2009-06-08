
#ifndef LMSRUNNER_H
#define LMSRUNNER_H

#include "Core/Exception.h"
#include "Core/Runner.h"

//TODO Document all algorithms! Don't forget to mention, that algorithms may be not correct,
//TODO especially for not obvious topologies. For ex. no tests with recurrent networks were made

namespace pann
{
    class LmsBackpropagationRunner : public Runner
    {
        LmsBackpropagationRunner();

    public:
        static RunnerPtr Instance()
        {
            static RunnerPtr self(new LmsBackpropagationRunner());
            return self;
        }
        
        virtual void run(NeuronPtr _neuron, NetPtr _net);

        virtual RunDirection getDirection()
        {
            return BackwardRun;
        }
 
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<LmsBackpropagationRunner, Runner>(
                    static_cast<LmsBackpropagationRunner*>(NULL),
                    static_cast<Runner*>(NULL));
            };
    };
}; //pann

#endif

