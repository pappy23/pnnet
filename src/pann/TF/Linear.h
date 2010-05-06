#ifndef PANN_TF_LINEAR_H_INCLUDED
#define PANN_TF_LINEAR_H_INCLUDED

#include "Core/Tf.h"

namespace pann {
    /**
     * Linear function
     * y = x
     * dy/dx = 0
     */
    class Linear : public Tf
    {
        SINGLETON_SKELETON(Linear, Tf);

        virtual Float fx(Float x) const
        {
            return x;
        }

        virtual Float df_dy(Float) const
        {
            return 1;
        }
    }; //Linear
    REGISTER_SINGLETON_H(Linear);

}; //pann

#endif //PANN_TF_LINEAR_H_INCLUDED

