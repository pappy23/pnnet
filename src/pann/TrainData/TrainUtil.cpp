//TrainUtil.cpp

#include "TrainUtil.h"

using namespace std;

namespace pann
{             
    namespace TrainUtil
    {
        valarray<Float>
        squash_copy(const valarray<Float> & _v, Float _min, Float _max)
        {
            valarray<Float> result = _v;
            squash(result, _min, _max);

            return _v;
        } //squash_copy

        void
        squash(valarray<Float> & _v, Float _min, Float _max)
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
        } //squash

    }; //TrainUtil
}; //pann

