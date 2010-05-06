#ifndef PANN_TF_TANH_H_INCLUDED
#define PANN_TF_TANH_H_INCLUDED

#include "Core/Tf.h"

namespace pann {
    /**
     * Hyperbolic tangent function
     * y = a*tanh(b*x)
     */
    class TanH : public Tf
    {
        TanH() : m_a( 1.7179 ), m_b( 2.0 / 3.0 ) {};
        SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(TanH, Tf);

        virtual Float fx(Float x) const
        {
            return m_a * std::tanh( m_b * x );
        }

        virtual Float df_dy(Float y) const
        {
            return m_b/m_a * (m_a - y) * (m_a + y);
        }

    private:
        const Float m_a;
        const Float m_b;
    }; //TanH
    REGISTER_SINGLETON_H(TanH);

}; //pann

#endif //PANN_TF_TANH_H_INCLUDED

