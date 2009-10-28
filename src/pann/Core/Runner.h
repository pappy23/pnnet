/*
 * @file
 * Generic runner interface
 */

#ifndef PANN_CORE_RUNNER_H_INCLUDED
#define PANN_CORE_RUNNER_H_INCLUDED

#include "Includes/BoostSerialization.h"
#include "Type.h"

namespace pann
{
    ADD_PTR_TYPEDEF(Neuron);
    ADD_PTR_TYPEDEF(Net);

    /**
     * Runner interface
     */
    class Runner
    {
    public:
        virtual void run(NeuronPtr, Net*) const = 0; //FIXME: replace Net* with shared_ptr<>
    };
    ADD_PTR_TYPEDEF(Runner);


}; //pann


#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

namespace pann {
namespace python {
    struct RunnerWrapper : Runner, boost::python::wrapper<Runner>
    {
        void run(NeuronPtr _neuron, Net* _net) const;
    };

    void export_Runner();
} //python
} //pann

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#endif //PANN_CORE_RUNNER_H_INCLUDED

