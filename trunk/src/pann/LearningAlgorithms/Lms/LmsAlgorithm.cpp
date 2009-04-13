//LmsAlgorithm.cpp

#include <vector>

#include <boost/foreach.hpp>

#include "LmsAlgorithm.h"
#include "LmsAttributes.h"
#include "LmsRunner.h"

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Runner.h"
#include "TrainData/TrainPattern.h"
#include "TrainData/TrainData.h"

using namespace std;
using namespace pann::LmsAttributes;

namespace pann
{
    void
    Lms::init(Net& _net)
    {
        if(!_net.is(LMS))
        {
            _net.erase(AlgorithmSpecificLearningParameters);
            _net[LMS] = 1.0;
        }

        //Simulated annealing
        //Set algorithm defaults. User can override them after init()
        _net[epoch] = 1;
        _net[learningMomentum] = 0.5;
        _net[learningRate] = 0.3;
        _net[annealingTSC] = 10;
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        if(!_net.is(LMS))
            //throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";
            init(_net);

        const vector<Neuron*>& output_neurons = _net.getCache().layers.back();

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(FeedforwardPropagationRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            
            //Put error information to output neurons
            for(unsigned i = 0; i < output_neurons.size(); ++i)
                (*output_neurons[i])[error] = tp.error[i];

            _net.run(LmsBackpropagationRunner::Instance());
            _net[epoch]++;
        }
    } //train

}; //pann

