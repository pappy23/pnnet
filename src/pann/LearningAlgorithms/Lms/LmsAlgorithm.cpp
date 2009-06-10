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

namespace pann
{
    //TODO: Use standart Backpropagation runner from Core

    void
    Lms::train(NetPtr _net, TrainData& _trainData)
    {
        const vector<NeuronPtr>& output_neurons = *(_net->getCache().layers.end() - 2);

        BOOST_FOREACH(TrainPattern& tp, _trainData.data)
        {
            _net->setInput(tp.input);
            _net->run(FeedforwardPropagationRunner::Instance());
            _net->getOutput(tp.error);
            tp.error = tp.desired_output - tp.error;

            //Put error information to output neurons
            for(unsigned i = 0; i < output_neurons.size(); ++i)
                output_neurons[i]->get<LmsNeuronAttributes>().error = tp.error[i];

            _net->run(LmsBackpropagationRunner::Instance());
            _net->get<LmsNetAttributes>().epoch++;
        }
    } //train

}; //pann

