#include <iostream>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;

void test(NetPtr net, Float start, Float stop, Float step);

Float func(Float _x)
{
    return sin(_x);
}

int main()
{
//*
    //Constructing perceptron
    vector<tuple<unsigned, ActivationFunctionPtr> > layers;
    layers.push_back(make_tuple(1, Linear::Instance())); //input  - no act. fcn
    layers.push_back(make_tuple(9, TanH::Instance())  ); //hidden - tanh
    layers.push_back(make_tuple(4, TanH::Instance())  ); //output - linear
    layers.push_back(make_tuple(1, Linear::Instance())); //output - linear
    NetPtr net = MultilayerPerceptron(layers);

    //Learning
    const unsigned epochs = 1000;
    TrainData& td = *(DataGenerator::generateFromFunction(-3.0, +3.0, 20, func));

    net->get<LmsNetAttributes>().learningRate = 0.3;
    net->get<LmsNetAttributes>().learningMomentum = 0.5;
    net->get<WeightRandomizationAttributes>().min = -0.6;
    net->get<WeightRandomizationAttributes>().max = +0.6;
    //net.run(RandomizeWeightsGaussRunner::Instance());
    net->run(RandomizeWeightsAccordingToInputsCountRunner::Instance());

    vector<Float> train_error_info; //MSE
    for(unsigned i = 1; i < epochs; ++i)
    {
        shuffle(td);
        Lms::train(net, td);

        train_error_info.push_back(ErrorFunction::mse(td));
    }

    test(net, -4.0, +4.0, +0.01);

    //Save trained net
    Storage::save<Storage::xml_out>(net, "test_lms.xml");

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

void test(NetPtr net, Float start, Float stop, Float step)
{
    //Test
    vector<Float> input, output, desired_output, error;

    unsigned i = 0;
    for(Float x = start; x < stop; x += step, ++i)
    {
        TrainPattern tmp(1, 1);
        tmp.input()[0] = x;
        tmp.desired_output()[0] = func(x);

        net->setInput(tmp.input());
        net->run(FeedforwardPropagationRunner::Instance());
        net->getOutput(tmp.actual_output()); //actual output

        input.push_back(x);
        desired_output.push_back(func(x));
        output.push_back(tmp.actual_output()[0]);
        error.push_back(tmp.error()[0]);
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
