
#include "TrainPattern.h"

using namespace std;

namespace pann
{             
    TrainPattern::TrainPattern(unsigned input_size, unsigned output_size)
    {
        resize(input_size, output_size);
    } //TrainPattern

    TrainPattern::~TrainPattern()
    {
    } //~TrainPattern

    void
    TrainPattern::resize(unsigned input_size, unsigned output_size)
    {
        input.resize(input_size);
        desired_output.resize(output_size);
        error.resize(output_size);
    } //resize  

    Float
    TrainPattern::getMse() const
    {
        if(desired_output.size() != error.size())
            throw SizeMismatch()<<"TrainPattern::getMse(): Error size doesn't match desired_output\n";

        //See Haykin, p225
        return (Float) ((error*error).sum()) / 2.0;
    } //getMse

}; //namespace pann

