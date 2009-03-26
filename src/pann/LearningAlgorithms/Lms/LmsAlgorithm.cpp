//LmsAlgorithm.cpp

#include "LmsAlgorithm.h"

namespace pann
{
    void
    Lms::init(Net& _net /* Params */)
    {
        /*
        if(_net.learningHint)
            delete _net.learningHint;

        LearningHint::LmsNet* net_lh = new LearningHint::LmsNet();
        _net.learningHint = (LearningHint::Base*) net_lh;
        net_lh->learningRate = 0.03;
        */
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        /*
        LearningHint::LmsNet* net_lh = dynamic_cast<LearningHint::LmsNet*>(_net.learningHint);
        if(!_net.learningHint || !net_lh)
            throw Exception::ObjectNotFound()<<"LMS::train(): Net was not initialized for LMS training\n";

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(LmsFeedforwardRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            _net.run(LmsBackpropagationRunner::Instance());
        }
        */
    } //train

}; //pann

