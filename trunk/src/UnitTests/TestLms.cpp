#include <iostream>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
//*
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); //input
    for(unsigned i = 0; i < 2; ++i)
        layers.push_back(5);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    TrainData td;
    for(signed i = -5; i < 6; ++i)
    {
        TrainPattern tp(1, 1);
        tp.input[0] = (Float) i / 10.0;
        tp.desired_output[0] =  i*i/100.0;
        td.data.push_back(tp);
    }

    Lms::init(*net);
    for(unsigned i = 0; i < 1000; ++i)
    {
        td.shuffle();
        Lms::train(*net, td);
//        cout<<"Train data:\n";
//        for(unsigned i = 0; i < td.data.size(); ++i)
//            cout<<fixed<<setprecision(3)<<"I="<<td.data[i].input[0]<<"\tT="<<td.data[i].desired_output[0]<<"\tE="<<td.data[i].error[0]<<endl;
        cout<<fixed<<setprecision(4)<<"E="<<td.getMse()<<endl;
    }

//*/
    Storage::save(*net, "test_lms.xml");
/*
    Net* n2 = new Net;
    Storage::load(*n2, "test_lms.xml");
*/
    return 0;
}
