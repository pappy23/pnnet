//LmsAlgorithm.cpp

#include "LmsAlgorithm.h"

namespace pann
{
    void
    Lms::init(Net& _net /* Params */)
    {
        if(!_net.learningHint.is(LmsAttributes::LMS))
        {
            _net.learningHint.erase();
            _net.learningHint[LmsAttributes::LMS] = 1.0;
        }

        _net.learningHint[LmsAttributes::learningRate] = 0.03;
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        if(!_net.learningHint.is(LmsAttributes::LMS))
            throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(LmsFeedforwardRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            _net.run(LmsBackpropagationRunner::Instance());
        }
    } //train

}; //pann

