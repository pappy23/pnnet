#ifndef ERRORFUNCTION_H
#define ERRORFUNCTION_H

#include <valarray>

#include "pann.h"
#include "TrainData.h"

namespace pann
{
    namespace ErrorFunction
    {
        Float mse(const TrainPattern& _tp);

        template<class T>
        Float mse(const T& _data)
        {
            Float res = 0;
            typename T::const_iterator iter = _data.begin();
            for(; iter != _data.end(); ++iter)
                res += mse(*iter);

            return res / Float(_data.size());
        }
    }; //ErrorFunction
}; //pann

#endif

