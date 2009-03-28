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
        _net.learningHint[LmsAttributes::learningMomentum] = 0.03;

        Util::randomizeWeightsGauss(_net, -0.03, 0.03);
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        if(!_net.learningHint.is(LmsAttributes::LMS))
            throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";

        map<unsigned, const Neuron*> output_neurons = _net.getOutputNeurons();

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(LmsFeedforwardRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            
            //Put error information to output neurons
            unsigned i = 0;
            map<unsigned, const Neuron*>::iterator iter = output_neurons.begin();
            for(; iter != output_neurons.end(); ++iter)
                const_cast<Neuron*>(iter->second)->learningHint[LmsAttributes::error] = tp.error[i++];

            _net.run(LmsBackpropagationRunner::Instance());
        }
        //TODO
        //1) calculate error for each iutput neuron
        //2) gradient descent
    } //train

}; //pann

