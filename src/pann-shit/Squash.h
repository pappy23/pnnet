#ifndef SQUASH_H
#define SQUASH_H

#include <valarray>

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
         * To squah range [src_min; src_max] to new range [dst_min; dst_max] we use this formula:
         *
         * N = ( ( dst_max - dst_min ) / ( src_max - src_min ) ) * N +
         *
         * + ( dst_max - ( ( dst_max - dst_min ) / ( src_max - src_min ) ) * src_max )
         */
        T a = ( dst_max - dst_min ) / ( src_max - src_min );
        T b = dst_max - a * src_max;
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

    template<class T>
    void shuffle(T& _data)
    {
        random_shuffle(_data.begin(), _data.end());
    } //shuffle

    template<class T>
    Float average(const T& _data)
    {
        Float res = 0;

        if(!_data.size())
            return 0;

        typename T::iterator iter = _data.begin();
        for(; iter != _data.end(); ++iter)
            res += *iter;

        return res / Float(_data.size());
    } //average

    template<class T>
    std::pair<T, T>
    divide(const T& _td, unsigned _percentage)
    {
        std::pair<T, T> result = make_pair(_td, T());
        unsigned count = unsigned(_td.size() * _percentage / 100.0);
        for(unsigned i = 0; i < count; i++)
        {
            result.second.push_back(result.first.back());
            result.first.pop_back();
        }

        return result;
    } //divide

}; //pann

#endif

