//TrainData.cpp

#include "TrainData.h"

#include "TrainPattern.h"

using namespace std;

namespace pann
{             
    TrainData::TrainData() throw()
    {
    } //TrainData

    TrainData::~TrainData() throw()
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
    TrainData::shuffle() throw()
    {
        random_shuffle(data.begin(), data.end());
    } //shuffle

}; //namespace pann

