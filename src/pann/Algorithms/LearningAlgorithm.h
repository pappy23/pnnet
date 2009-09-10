/**
 * @file
 * ////Abstract for all learning algorithms
 */

#ifndef TEST_H
#define TEST_H

#include "Core/Type.h"
#include "Core/Net.h"
#include "Core/Runner.h"
#include "TrainData/TrainData.h"

namespace pann
{
    template<class T>
    void test(NetPtr _net, T& _td)
    {
        typename T::iterator iter = _td.begin();
        for(; iter != _td.end(); ++iter)
        {
            _net->setInput(iter->input());
            _net->run(FeedforwardPropagationRunner::Instance());
            _net->getOutput(iter->actual_output());
        }
    }

}; //pann

#endif

