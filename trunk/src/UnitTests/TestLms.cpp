#include <iostream>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

Float func(Float _x)
{
    return sin(_x);
}

int main()
{
//*
    //Constructing perceptron
    vector<unsigned> layers;
    layers.push_back(1); //input
    for(unsigned i = 0; i < 2; ++i)
        layers.push_back(50);
    layers.push_back(1); //output
    Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

    //Data
    //boost::function<Float (Float)> f = (_1 += 10); //boost::lambda::bind( (Float (*)(Float))sin, _1 );
    //boost::function<Float (Float)> f = boost::bind( (Float (*)(Float))func, _1);

    //Learning
    const unsigned epochs = 20;
    vector<Float> train_error_info; //MSE

    Lms::init(*net);
    net->learningHint[LmsAttributes::learningRate] = 0.01;
    
    boost::progress_display progress(epochs);
    for(unsigned i = 0; i < epochs; ++i)
    {
        ++progress;

        TrainData& td = *(DataGenerator::generateFromFunction(-3.0, +3.0, 100, func));
        //td->shuffle();
        
        Lms::train(*net, td);
        
        train_error_info.push_back(td.getMse());
    }

    //Save trained net
    Storage::save(*net, "test_lms.xml");

    //Test
    const Float start = -3.0;
    const Float stop  = +3.0;
    const Float step  =  0.1;
    TrainPattern test_info((stop-start)/step, (stop-start)/step);
    unsigned i = 0;
    for(Float x = start; x < stop; x += step, ++i)
    {
        TrainPattern tmp(1, 1);
        tmp.input[0] = x;
        tmp.desired_output[0] = func(x);

        net->setInput(tmp.input);
        net->run(FeedforwardPropagationRunner::Instance());
        net->getOutput(tmp.error); //actual output

        test_info.input[i] = tmp.input[0];
        test_info.desired_output[i] = tmp.desired_output[0];
        test_info.error[i] = tmp.desired_output[0] - tmp.error[0];
    }

    try {
        Gnuplot gp_err("lines");
        gp_err.set_title("Error by epoch");
        gp_err.plot_x(train_error_info);

        Gnuplot gp_test("points");
        gp_test.set_title("Test");
        gp_test.set_smooth().plot_xy(test_info.input, test_info.error, "Error");
        gp_test.set_smooth().plot_xy(test_info.input, test_info.desired_output, "Desired output");
        gp_test.set_smooth().plot_xy(test_info.input, test_info.desired_output - test_info.error, "Output");

        cout<<"Press ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }

//*/
/*
    Net* n2 = new Net;
    Storage::load(*n2, "test_lms.xml");
*/
    return 0;
}

