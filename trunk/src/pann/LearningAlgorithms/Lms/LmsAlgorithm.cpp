//LmsAlgorithm.cpp

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"

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
using namespace boost;
using namespace pann::AttributesGroup;

namespace pann
{
    void
    Lms::init(Net& _net)
    {
        LmsNetAttributesPtr attrs = _net.at<LmsNetAttributes>(LmsNet);
        if(!attrs)
            attrs.reset(new LmsNetAttributes);

        //Simulated annealing
        //Set algorithm defaults. User can override them after init()
        attrs->epoch = 1;
        attrs->learningMomentum = 0.5;
        attrs->learningRate = 0.3;
        attrs->annealingTSC = 10;
    } //init

    void
    Lms::train(Net& _net, TrainData& _trainData)
    {
        LmsNetAttributesPtr attrs = _net.at<LmsNetAttributes>(LmsNet);
        if(!attrs)
            //throw E<Exception::ObjectNotFound>()<<"LMS::train(): Net was not initialized for LMS training\n";
            init(_net);

        const vector<NeuronPtr>& output_neurons = _net.getCache().layers.back();

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net.setInput(tp.input);
            _net.run(FeedforwardPropagationRunner::Instance());
            _net.getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;
            
            //Put error information to output neurons
            for(unsigned i = 0; i < output_neurons.size(); ++i)
                output_neurons[i]->at(error) = tp.error[i];

            _net.run(LmsBackpropagationRunner::Instance());
            _net[epoch]++;
        }
    } //train

}; //pann

