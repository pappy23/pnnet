#include <iostream>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
/*
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); //input
    for(unsigned i = 0; i < 1; ++i)
        layers.push_back(2);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    TrainData td;
    for(unsigned i = 0; i < 10; ++i)
    {
        TrainPattern tp(1, 1);
        tp.input[0] = i;
        tp.desired_output[0] = -i;
        td.data.push_back(tp);
    }

    for(unsigned i = 0; i < 10; ++i)
    {
        td.shuffle();
        LMS::init(*net);
        LMS::train(*net, td);
        cout<<"E="<<td.getMse()<<endl;
    }

    Storage::save(*net, "test_lms.xml");
//*/
    Net* n2 = new Net;
    Storage::load(*n2, "test_lms.xml");

    return 0;
}

