#include <iostream>

#include <boost/progress.hpp>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;

void test(Net& net, Float start, Float stop, Float step);

Float func(Float _x)
{
    return sin(_x); // * _x;
}

const unsigned epochs = 10;

int main()
{
//*
    //Constructing perceptron
    vector<tuple<unsigned, ActivationFunction::Base*> > layers;
    layers.push_back(make_tuple(1, ActivationFunction::Linear::Instance())); //input  - no act. fcn
    layers.push_back(make_tuple(16,ActivationFunction::TanH::Instance())  ); //hidden - tanh
    layers.push_back(make_tuple(9, ActivationFunction::TanH::Instance())  ); //hidden - tanh
    layers.push_back(make_tuple(4, ActivationFunction::TanH::Instance())  ); //output - linear
    layers.push_back(make_tuple(1, ActivationFunction::Linear::Instance())); //output - linear
    Net& net = MultilayerPerceptron(layers);

    //Data
    //boost::function<Float (Float)> f = (_1 += 10); //boost::lambda::bind( (Float (*)(Float))sin, _1 );
    //boost::function<Float (Float)> f = boost::bind( (Float (*)(Float))func, _1);

    //Learning
    vector<Float> train_error_info; //MSE

    TrainData& td = *(DataGenerator::generateFromFunction(-3.0, +3.0, 10, func));

    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.2;
    net[LmsAttributes::annealingTSC] = 3000;
    net[RandomizeWeightsAttributes::min] = -0.6;
    net[RandomizeWeightsAttributes::max] = +0.6;
    //net.run(RandomizeWeightsGaussRunner::Instance());
    net.run(RandomizeWeightsAccordingToInputsCountRunner::Instance());
    Lms::train(net, td); //dry run to create all learning structures
    
    boost::progress_display progress(epochs);
    for(unsigned i = 1; i < epochs; ++i)
    {
        ++progress;
        td.shuffle();
        Lms::train(net, td);
        train_error_info.push_back(td.getMse());
    }

//    test(net, -2.0, +2.0, +0.01);

    //Save trained net
    //Storage::save<Storage::xml_out>(net, "test_lms.xml");

    //Plotting error graph
    /*
    try {
        Gnuplot gp_err("lines");
        gp_err.set_title("Error by epoch");
        gp_err.plot_x(train_error_info);

        cout<<"Press ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }
    */
    return 0;
}

void test(Net& net, Float start, Float stop, Float step)
{
    //Test
    vector<Float> input, output, desired_output, error;

    unsigned i = 0;
    for(Float x = start; x < stop; x += step, ++i)
    {
        TrainPattern tmp(1, 1);
        tmp.input[0] = x;
        tmp.desired_output[0] = func(x);

        net.setInput(tmp.input);
        net.run(FeedforwardPropagationRunner::Instance());
        net.getOutput(tmp.error); //actual output

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
