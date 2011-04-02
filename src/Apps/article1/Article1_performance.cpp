#include <iostream>

#include "pann-shit.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;

int main()
{
#ifdef UNIX
    cout<<"kuku\n";
#endif
    //Constructing perceptron
    vector<boost::tuple<unsigned, TfPtr> > layers;
    layers.push_back(make_tuple(1, Linear::Instance()));  //input  - no act. fcn
    layers.push_back(make_tuple(1000, TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1000, TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1000, TanH::Instance())); //hidden - tanh
    layers.push_back(make_tuple(1, Linear::Instance()));  //output - linear
    NetPtr net = MultilayerPerceptron(layers);


    //Learning
    TrainData td;
    TrainPattern tp(1,1);
    tp.input()[0] = 1;
    tp.desired_output()[0] = 1;
    td.push_back(tp);

    //net->run(RandomizeWeightsGaussRunner::Instance());
    randomize_weights_gauss(net, -0.3, +0.3);
    lms_init(net);
    Lms::train(net, td); //dry run to create all learning structures

    for(unsigned i = 1; i < 9; ++i)
    {
        cout<<i<<" threads\n";
#ifdef UNIX
        struct timeval start, stop;
        gettimeofday(&start, 0);
#endif

        net->set_work_threads_count(i);
        Lms::train(net, td);
#ifdef UNIX
        gettimeofday(&stop, 0);
        cout<<"TimeDiff: "<<(stop.tv_sec-start.tv_sec)<<"sec "<<(stop.tv_usec-start.tv_usec)<<"usec\n\n";
#endif
    }

    return 0;
}

