#include <iostream>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); 
    layers.push_back(1000); 
    layers.push_back(1000); 
    layers.push_back(1000); 
    layers.push_back(1); 
    Net& net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Learning
    TrainData td;
    TrainPattern tp(1,1);
    tp.input[0] = 1; tp.desired_output[0] = 1;
    td.data.push_back(tp);

    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.2;
    net[LmsAttributes::learningMomentum] = 0.5;
    Util::randomizeWeightsGauss(net, -0.3, 0.3);
    Lms::train(net, td); //dry run to create all learning structures
    
    for(unsigned i = 1; i < 9; ++i)
    {
        cout<<i<<" threads\n";
        struct timeval start, stop;
        gettimeofday(&start, 0);

        Lms::train(net, td, i);
        
        gettimeofday(&stop, 0);
        cout<<"TimeDiff: "<<(stop.tv_sec-start.tv_sec)<<"sec "<<(stop.tv_usec-start.tv_usec)<<"usec\n\n";
    }

    return 0;
}

