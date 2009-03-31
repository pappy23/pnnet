#include <iostream>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

Float func(Float _x)
{
    return _x / 2.0;
}

int main()
{
//*
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); //input
    for(unsigned i = 0; i < 4; ++i)
        layers.push_back(2);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    //boost::function<Float (Float)> f = (_1 += 10); //boost::lambda::bind( (Float (*)(Float))sin, _1 );
    
    //boost::function<Float (Float)> f = boost::bind( (Float (*)(Float))func, _1);
    TrainData* td = DataGenerator::generateFromFunction(-3.0, +3.0, 100, func);

    Lms::init(*net);
    net->learningHint[LmsAttributes::learningRate] = 0.01;
    for(unsigned i = 0; i < 1000; ++i)
    {
        td->shuffle();
        Lms::train(*net, *td);
//        cout<<"Train data:\n";
//        for(unsigned j = 0; j < td->data.size(); ++j)
//            cout<<fixed<<setprecision(3)<<"I="<<td->data[j].input[0]<<"\tT="<<td->data[j].desired_output[0]<<"\tE="<<td->data[j].error[0]<<endl;
        cout<<i+1<<"\t"<<fixed<<setprecision(4)<<td->getMse()<<endl;
    }
    Storage::save(*net, "test_lms.xml");

//*/
/*
    Net* n2 = new Net;
    Storage::load(*n2, "test_lms.xml");
*/
    return 0;
}

