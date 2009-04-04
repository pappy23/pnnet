#include <iostream>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

void test(Net* net, Float start, Float stop, Float step);

Float func(Float _x)
{
    return _x * _x / 50.0;
}

int main()
{
//*
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); //input
    layers.push_back(50);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    //boost::function<Float (Float)> f = (_1 += 10); //boost::lambda::bind( (Float (*)(Float))sin, _1 );
    //boost::function<Float (Float)> f = boost::bind( (Float (*)(Float))func, _1);

    //Learning
    const unsigned epochs = 5;
    vector<Float> train_error_info; //MSE

    TrainData& td = *(DataGenerator::generateFromFunction(-3.5, +3.5, 100, func));

    Lms::init(*net);
    net->learningHint[LmsAttributes::learningRate] = 0.1;
    net->learningHint[LmsAttributes::learningMomentum] = 0.5;
    
    boost::progress_display progress(epochs);
    {
    boost::progress_timer t;
    for(unsigned i = 0; i < epochs; ++i)
    {
        ++progress;

        td.shuffle();
        
        Lms::train(*net, td);
        
        train_error_info.push_back(td.getMse());
        //cout<<td.getMse()<<endl;
    }
    }

    test(net, -3.5, +3.5, +0.01);

    //Save trained net
    Storage::save(*net, "test_lms.xml");

    //Plotting error graph
    try {
        Gnuplot gp_err("lines");
        gp_err.set_title("Error by epoch");
        gp_err.plot_x(train_error_info);

        cout<<"Press ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }

    return 0;
}

void test(Net* net, Float start, Float stop, Float step)
{
    //Test
    vector<Float> input, output, desired_output, error;

    unsigned i = 0;
    for(Float x = start; x < stop; x += step, ++i)
    {
        TrainPattern tmp(1, 1);
        tmp.input[0] = x;
        tmp.desired_output[0] = func(x);

        net->setInput(tmp.input);
        net->run(FeedforwardPropagationRunner::Instance());
        net->getOutput(tmp.error); //actual output

        input.push_back(x);
        desired_output.push_back(func(x));
        output.push_back(tmp.error[0]);
        error.push_back(tmp.desired_output[0] - tmp.error[0]);
    }

    try {
        Gnuplot gp_test("points");
        gp_test.set_title("Test");
        gp_test.set_smooth().plot_xy(input, error, "Error");
        gp_test.set_smooth().plot_xy(input, desired_output, "Desired output");
        gp_test.set_smooth().plot_xy(input, output, "Output");

        cout<<"Press ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }

}; //test
