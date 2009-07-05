#include <iostream>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
#ifdef UNIX
    cout<<"kuku\n";
#endif
    //Constructing perceptron
    vector<tuple<unsigned, ActivationFunction::Base*> > layers;
    layers.push_back(make_tuple(1, ActivationFunction::Linear::Instance()));  //input  - no act. fcn
    layers.push_back(make_tuple(1000, ActivationFunction::TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1000, ActivationFunction::TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1000, ActivationFunction::TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1, ActivationFunction::Linear::Instance()));  //output - linear
    NetPtr net_ptr = MultilayerPerceptron(layers);
    Net& net = *net_ptr;


    //Learning
    TrainData td;
    TrainPattern tp(1,1);
    tp.input[0] = 1; tp.desired_output[0] = 1;
    td.data.push_back(tp);

    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.2;
    net[LmsAttributes::learningMomentum] = 0.5;
    net[RandomizeWeightsAttributes::min] = -0.3;
    net[RandomizeWeightsAttributes::max] = +0.3;
    //net.run(RandomizeWeightsGaussRunner::Instance());
    net.run(RandomizeWeightsAccordingToInputsCountRunner::Instance());
    Lms::train(net, td); //dry run to create all learning structures
    
    for(unsigned i = 1; i < 9; ++i)
    {
        cout<<i<<" threads\n";
#ifdef UNIX
        struct timeval start, stop;
        gettimeofday(&start, 0);
#endif

        net.setWorkThreadsCount(i);
        Lms::train(net, td);
#ifdef UNIX
        gettimeofday(&stop, 0);
        cout<<"TimeDiff: "<<(stop.tv_sec-start.tv_sec)<<"sec "<<(stop.tv_usec-start.tv_usec)<<"usec\n\n";
#endif
    }

    return 0;
}
