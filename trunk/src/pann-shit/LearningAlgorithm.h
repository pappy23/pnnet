/**
 * @file
 * ////Abstract for all learning algorithms
 */

#ifndef TEST_H
#define TEST_H

#include "pann.h"
#include "TrainData.h"

namespace pann
{
    template<class T>
    void test(NetPtr _net, T& _td)
    {
        typename T::iterator iter = _td.begin();
        for(; iter != _td.end(); ++iter)
        {
            _net->set_input(iter->input());
            _net->run(FeedforwardPropagationRunner::Instance());
            _net->get_output(iter->actual_output());
        }
    }

}; //pann

#endif

