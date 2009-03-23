#ifndef TRAINDATA_H
#define TRAINDATA_H

#include "Includes.h"
#include "Exception.h"
#include "Type.h"
#include "Object.h"

namespace pann
{
    class TrainUtil
    {
    public:
        static std::valarray<Float> squash_copy(const std::valarray<Float> & _v, Float _min, Float _max);
        static void squash(std::valarray<Float> & _v, Float _min, Float _max);
    };

    class TrainPattern : public Object
    {
        /* Public interface */
    public:
        TrainPattern(unsigned input_size, unsigned output_size);
        ~TrainPattern();

        Float getMse() const;

        /* Public members */
    public:
        std::valarray<Float> input;
        std::valarray<Float> desired_output;
        std::valarray<Float> error;

        /* Private methods */
    private:
        TrainPattern();
        void resize(unsigned input_size, unsigned output_size);
    };

    class TrainData : public Object
    {
        /* Public interface */
    public:
        TrainData();
        ~TrainData();

        Float getMse() const;
        void shuffle();

        /* Public members */
    public:
        std::vector<TrainPattern> data;
    };

}; //pann

#endif

