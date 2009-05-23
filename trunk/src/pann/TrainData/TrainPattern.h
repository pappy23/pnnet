#ifndef TRAINPATTERN_H
#define TRAINPATTERN_H

#include <valarray>

#include "Core/Exception.h"
#include "Core/Type.h"

namespace pann
{
    class TrainPattern
    {
        /* Public interface */
    public:
        TrainPattern(unsigned input_size, unsigned output_size);
        virtual ~TrainPattern();

        Float getMse() const;

        /* Public members */
    public:
        std::valarray<Float> input;
        std::valarray<Float> desired_output;
        std::valarray<Float> error;

        /* Private methods */
    private:
        void resize(unsigned input_size, unsigned output_size);
    };
}; //pann

#endif

