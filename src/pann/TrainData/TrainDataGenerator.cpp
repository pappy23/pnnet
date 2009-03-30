//TrainDataGenerator.cpp

#include "TrainDataGenerator.h"

namespace pann
{
    namespace DataGenerator
    {
        TrainData*
        generateFromFunction(Float _min, Float _max, unsigned _count, boost::function<Float (Float _x)> _f)
        {
            TrainData* td = new TrainData();

            for(unsigned i = 0; i < _count; ++i)
            {
                TrainPattern tp(1, 1);
                tp.input[0] = Util::rand(_min, _max);
                tp.desired_output[0] = _f(tp.input[0]);
                td->data.push_back(tp);
            }

            return td;
        } //generateFromFunction

    }; //DataGenerator
}; //pann

