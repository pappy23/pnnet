//Runner.cpp

#include "Runner.h"
#include "Net.h"

namespace pann {
}; //pann

#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

namespace pann {
namespace python {
    void
    RunnerWrapper::run(NeuronPtr _neuron, Net* _net) const
    {
        this->get_override("run")(_neuron, _net);
    }

    void
    export_Runner()
    {
        using namespace boost::python;

        class_<RunnerWrapper, boost::noncopyable>("Runner")
            .def("run", pure_virtual(&Runner::run))
            ;
    }
} //python
} //pann

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

