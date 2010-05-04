//Python.cpp

#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

#include "All.h"

BOOST_PYTHON_MODULE(libpann)
{
    using namespace pann::python;

    export_Moo();
    export_Runner();
    export_Weight();
}

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

