//Python.cpp

#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

#include "All.h"

BOOST_PYTHON_MODULE(libpann)
{
    using namespace boost::python;

    python_export_Moo();
}

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

