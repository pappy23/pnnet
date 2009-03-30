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
    for(unsigned i = 0; i < 4; ++i)
        layers.push_back(10);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    //boost::function<Float (Float)> f = (_1 += 10); //boost::lambda::bind( (Float (*)(Float))sin, _1 );
    
    boost::function<Float (Float)> f = boost::bind( (Float (*)(Float))sin, _1);
    TrainData* td = DataGenerator::generateFromFunction(-0.5, +0.5, 200, f);

    Lms::init(*net);
    for(unsigned i = 0; i < 1000; ++i)
    {
        td->shuffle();
        Lms::train(*net, *td);
//        cout<<"Train data:\n";
//        for(unsigned i = 0; i < td->data.size(); ++i)
//            cout<<fixed<<setprecision(3)<<"I="<<td->data[i].input[0]<<"\tT="<<td->data[i].desired_output[0]<<"\tE="<<td->data[i].error[0]<<endl;
        cout<<fixed<<setprecision(4)<<td->getMse()<<endl;
    }

//*/
//    Storage::save(*net, "test_lms.xml");
/*
    Net* n2 = new Net;
    Storage::load(*n2, "test_lms.xml");
*/
    return 0;
}

