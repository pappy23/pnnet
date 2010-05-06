#ifndef PANN_TF_THRESHOLD_H_INCLUDED
#define PANN_TF_THRESHOLD_H_INCLUDED

#include "Core/Tf.h"

namespace pann {
    /**
     * MacCalloc-Pitz threshold function
     * y = 0, x <0
     * y = 1, x>=0
     */
    class Threshold : public Tf
    {
        SINGLETON_SKELETON(Threshold, Tf);

        virtual Float fx(Float x) const
        {
            if(x < 0)
                return 0;
            return 1;
        }

        virtual Float df_dy(Float y) const
        {
            if(y == 0)
                return inf;

            return 0;
        }
    }; //Threshold
    REGISTER_SINGLETON_H(Threshold);

}; //pann

#endif //PANN_TF_THRESHOLD_H_INCLUDED

