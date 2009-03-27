//LmsAlgorithm.cpp

#include "LmsAlgorithm.h"

using namespace std;

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

        Lms::randomizeWeightsGauss(_net, -0.03, 0.03);
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

    Float
    Lms::randFloat(Float _min, Float _max) throw()
    {
        //TODO use boost::random for this (for ex. Mersenne twister)
        return ( (_max - _min) * ( (Float) rand() / (RAND_MAX+1) ) ) + _min;
    } //randFloat

    void
    Lms::randomizeWeightsGauss(Net& _net, Float _min, Float _max) throw()
    {
        map<unsigned, Neuron*>::const_iterator n_iter = _net.getNeurons().begin();
        for(; n_iter != _net.getNeurons().end(); ++n_iter)
        {
            list<Link>::const_iterator l_iter = n_iter->second->links.begin();
            for(; l_iter != n_iter->second->links.end(); ++l_iter)
            {
                if(l_iter->getDirection() == Link::in)
                {
                    const_cast<Link&>(*l_iter).getWeight()->value = randFloat(_min, _max);
                }
            }
        }
    } //randomizeWeightsGauss

}; //pann

