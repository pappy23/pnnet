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
    public:
        std::valarray<Float> input;
        std::valarray<Float> desired_output;
        std::valarray<Float> error;

    private:
        TrainPattern();
        void resize(unsigned input_size, unsigned output_size);

    public:
        TrainPattern(unsigned input_size, unsigned output_size);
        ~TrainPattern();

        Float getMse();

    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<"TrainPattern\n";
            ost<<"  inputs: "<<input.size()<<std::endl;
            ost<<"  desired_outputs: "<<desired_output.size()<<std::endl;
            ost<<"  errors: "<<error.size()<<std::endl;
        };
    };

    class TrainData : public Object
    {
    public:
        std::vector<TrainPattern> data;

    public:
        Float getMse();
    };

}; //pann

#endif

