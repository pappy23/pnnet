#include "TrainData.h"

using namespace std;

namespace pann
{             
    valarray<Float>
    TrainUtil::squash_copy(const valarray<Float> & _v, Float _min, Float _max)
    {
        valarray<Float> result = _v;
        squash(result, _min, _max);

        return _v;
    } //squash

    void
    TrainUtil::squash(valarray<Float> & _v, Float _min, Float _max)
    {
        if(_min > _max)
            swap(_min, _max);

        Float min = _v.min();
        Float max = _v.max();

        if(max == min) //very strange
        {
            _v = (Float) (_max + _min) / 2;
            return;
        }

        /*
         * To squah range [min; max] to new range [_min; _max] we use this formula:
         *
         * N = ( ( _max - _min ) / ( max - min ) ) * N +
         *      
         *      + ( _max - ( ( _max - _min ) / ( max - min ) ) * max )
         */
        Float a = ( _max - _min ) / ( max - min );
        Float b = _max - a * max;
        _v = a * _v + b;
    } //squash_by_ref

    TrainPattern::TrainPattern()
    {
        resize(0, 0);
    } //TrainPattern

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
            throw Exception::SizeMismatch()<<"TrainPattern::getMse(): Error size doesn't match desired_output\n";

        return (Float) ((error*error).sum()) / error.size();
    } //getMse

    TrainData::TrainData()
    {
    } //TrainData

    TrainData::~TrainData()
    {
    } //~TrainData

    Float
    TrainData::getMse() const
    {
        Float result = 0;

        if(data.size() == 0)
            return 0;

        vector<TrainPattern>::const_iterator iter = data.begin();
        for(; iter != data.end(); iter++)
            result += iter->getMse();

        return result / data.size();
    } //getMse

    void
    TrainData::shuffle()
    {
        random_shuffle(data.begin(), data.end());
    } //shuffle

}; //namespace pann

