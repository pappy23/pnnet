//Weight.cpp

#include "Weight.h"

namespace pann {
}; //pann


#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

namespace pann {
namespace python {
    void export_Weight()
    {
        using namespace boost::python;

        class_<Weight, boost::noncopyable>("Weight", init<Float>())
            ;
    }
}; //python
}; //pann

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

