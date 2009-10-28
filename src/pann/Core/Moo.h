/**
 * A little Easter egg =)
 */
#ifndef PANN_CORE_MOO_H_INCLUDED
#define PANN_CORE_MOO_H_INCLUDED

namespace pann {
    void moo();
}; //pann

#endif //PANN_CORE_MOO_H_INCLUDED

#ifdef OPTION_BUILD_PYTHON_BINDINGS_DEFINED

#include "Includes/Python.h"

namespace pann {
namespace python {
    void export_Moo();
}; //python
}; //pann

#endif //OPTION_BUILD_PYTHON_BINDINGS_DEFINED

