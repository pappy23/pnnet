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

        //Set algorithm defaults. User can override them after init()
        _net.learningHint[LmsAttributes::learningRate] = 0.3;
        _net.learningHint[LmsAttributes::learningMomentum] = 0.1;

        Util::randomizeWeightsGauss(_net, -0.03, 0.03);
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        if(!_net.learningHint.is(LmsAttributes::LMS))
            throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";

        const vector<Neuron*>& output_neurons = _net.getCache().layers.back();

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(LmsFeedforwardRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            
            //Put error information to output neurons
            for(unsigned i = 0; i < output_neurons.size(); ++i)
                output_neurons[i]->learningHint[LmsAttributes::error] = tp.error[i];

            _net.run(LmsBackpropagationRunner::Instance(), 1);
        }
    } //train

}; //pann

