/**
 * @file
 * ////Abstract for all learning algorithms
 */

#ifndef TEST_H
#define TEST_H

#include "Core/Net.h"
#include "Runners/FeedforwardPropagationRunner.h"
#include "TrainData_move_to_python/TrainData.h"

namespace pann
{
    template<class T>
    void test(NetPtr _net, T& _td)
    {
        typename T::iterator iter = _td.begin();
        for(; iter != _td.end(); ++iter)
        {
            _net->setInput(iter->input());
            _net->run(Net::ForwardRun, FeedforwardPropagationRunner::Instance());
            _net->getOutput(iter->actual_output());
        }
    }

}; //pann

#endif

