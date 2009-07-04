//ErrorFunction.cpp

#include "ErrorFunction.h"

using std::valarray;
using std::vector;

namespace pann
{
    namespace ErrorFunction
    {
        Float
        mse(const TrainPattern& _tp)
        {
            if(_tp.desired_output().size() != _tp.actual_output().size())
                throw SizeMismatch()<<"Actual output size differs from desired output vector\n";

            //See Haykin, p225
            valarray<Float> error = _tp.error();
            return (Float) ((error*error).sum()) / 2.0;
        }; //mse

    }; //ErrorFunction
}; //pann
