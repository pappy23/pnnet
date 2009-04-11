//LmsAlgorithm.cpp

#include "LmsAlgorithm.h"

using namespace std;

namespace pann
{
    void
    Lms::init(Net& _net)
    {
        AttributesManager net_hint(&_net);
        (&_net)->run(LmsFeedforwardRunner::Instance());
        std::cout<<"ok\n";

        if(!net_hint.is(LmsAttributes::LMS))
        {
            net_hint.erase(AlgorithmSpecificLearningParameters);
            net_hint[LmsAttributes::LMS] = 1.0;
        }

        //Set algorithm defaults. User can override them after init()
        net_hint[LmsAttributes::learningRate] = 0.3;
        net_hint[LmsAttributes::learningMomentum] = 0.5;
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        AttributesManager net_hint(&_net);
        if(!net_hint.is(LmsAttributes::LMS))
            //throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";
            init(_net);

        const vector<Neuron*>& output_neurons = _net.getCache().layers.back();

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(LmsFeedforwardRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            
            //Put error information to output neurons
            for(unsigned i = 0; i < output_neurons.size(); ++i)
            {
                AttributesManager neuron_hint(output_neurons[i]);
                neuron_hint[LmsAttributes::error] = tp.error[i];
            }

            _net.run(LmsBackpropagationRunner::Instance());
        }
    } //train

}; //pann

