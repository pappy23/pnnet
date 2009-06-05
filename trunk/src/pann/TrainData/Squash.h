#ifndef SQUASH_H
#define SQUASH_H

#include "Includes/Std.h"

using namespace std;

namespace pann
{
    template<typename T, typename U1, typename U2, typename U3, typename U4>
    void squash(valarray<T>& _v, U1 _src_min, U2 _src_max,
                                 U3 _dst_min, U4 _dst_max)
    {
        T src_min = (T) _src_min;
        T src_max = (T) _src_max;
        T dst_min = (T) _dst_min;
        T dst_max = (T) _dst_max;

        if(src_min > src_max)
            swap(src_min, src_max);

        if(dst_min > dst_max)
            swap(dst_min, dst_max);

        if(src_min > _v.min() || src_max < _v.max())
            throw Exception()<<"Source range mismatch\n";

        //This check eliminates division by zero in some
        //strange conditions
        if(dst_max == dst_min)
        {
            _v = (T) (src_max + src_min) / 2;
            return;
        }

        /*
         * To squah range [min; max] to new range [_min; _max] we use this formula:
         *
         * N = ( ( _src_max - _src_min ) / ( _dst_max - _dst_min ) ) * N +
         *      
         * + ( _src_max - ( ( _src_max - _src_min ) / ( _dst_max - _dst_min ) ) * _dst_max )
         */
        T a = ( src_max - src_min ) / ( dst_max - dst_min );
        T b = src_max - a * dst_max;
        _v = a * _v + b;
    } //squash

    template<typename T, typename U1, typename U2, typename U3, typename U4>
    valarray<Float> squash_copy(const valarray<T>& _v,
                                U1 _src_min, U2 _src_max,
                                U3 _dst_min, U4 _dst_max)
    {
        valarray<T> result = _v;
        squash(result, _src_min, _src_max, _dst_min, _dst_max);

        return result;
    } //squash_copy

}; //pann

#endif
