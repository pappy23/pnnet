#include "TrainPattern.h"

using namespace std;

namespace pann
{             
    TrainPattern::TrainPattern(unsigned input_size, unsigned output_size) throw()
    {
        resize(input_size, output_size);
    } //TrainPattern

    TrainPattern::~TrainPattern() throw()
    {
    } //~TrainPattern

    void
    TrainPattern::resize(unsigned input_size, unsigned output_size) throw()
    {
        input.resize(input_size);
        desired_output.resize(output_size);
        error.resize(output_size);
    } //resize  

    Float
    TrainPattern::getMse() const throw(E<Exception::SizeMismatch>)
    {
        if(desired_output.size() != error.size())
            throw E<Exception::SizeMismatch>()<<"TrainPattern::getMse(): Error size doesn't match desired_output\n";

        //See Haykin, p225
        return (Float) ((error*error).sum()) / 2.0;
    } //getMse

}; //namespace pann

