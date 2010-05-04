/**
 * @file
 * Activation functions interface
 */

#ifndef PANN_CORE_TF_H_INCLUDED
#define PANN_CORE_TF_H_INCLUDED

#include "Type.h"

namespace pann
{
    /**
     * All activation functions inherit Tf
     * (Transfer function)
     */
    class Tf
    {
    public:
        virtual Float f(Float) const = 0;
        virtual Float df_dy(Float) const = 0;
    }; //Tf
    ADD_PTR_TYPEDEF(Tf);

}; //pann

#endif //PANN_CORE_TF_H_INCLUDED

