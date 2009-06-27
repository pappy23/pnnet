//RandomizeWeights.cpp

#include "Core/Net.h"
#include "Core/Runner.h"
#include "TrainData/TrainPattern.h"
#include "TrainData/TrainData.h"

namespace pann
{
    void test(NetPtr _net, TrainData& _td)
    {
        for(unsigned i = 0; i < _td.data.size(); ++i)
        {
            _net->setInput(_td.data[i].input);
            _net->run(FeedforwardPropagationRunner::Instance());
            std::valarray<Float> output;
            _net->getOutput(output); //actual output
            _td.data[i].error = _td.data[i].desired_output - output;
        }
    }; //test

}; //pann

