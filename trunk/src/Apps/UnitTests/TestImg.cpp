#include <iostream>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/progress.hpp>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;
using namespace boost::gil;

void rgb2jpeg(int _r, int _g, int _b, string _filename, int _w, int _h)
{
    rgb8_image_t img = rgb8_image_t(_w, _h);
    fill_pixels(view(img), rgb8_pixel_t(_r, _g, _b));
    jpeg_write_view(_filename, view(img));
} //rgb2jpeg

Float func(Float _x)
{
    return _x * _x;
}

int main(int argc, char* argv[])
{
    TrainData td;
    unsigned images[][3] = {
        {255, 0,   0  },
        {0,   255, 0  },
        {0,   0,   255},
        {255, 255, 255},
        {128, 128, 0  },
        {0,   128, 128},
        {128, 0,   128},
        {50,  50,  50 },
        {150, 140, 40 },
        {0,   10,  20 }
    };
    for(unsigned i = 0; i < 10; ++i)
    {
        rgb2jpeg(images[i][0], images[i][1], images[i][2], lexical_cast<string>(i)+".jpg", 10, 10);

        try {
            TrainPattern tp(300, 3);
            tp.input = Util::squash_copy(
                    DataGenerator::jpeg_rgb2valarray(lexical_cast<string>(i) + ".jpg", 10, 10), 
            -1.5, +1.5);
            tp.desired_output[0] = images[i][0];
            tp.desired_output[1] = images[i][1];
            tp.desired_output[2] = images[i][2];
            Util::squash(tp.desired_output, -1.5, +1.5);
            td.data.push_back(tp);
        } catch(...) {
            cout<<"Failed to read "<<i<<".jpg\n";
        }
    }

    /*
    BOOST_FOREACH( TrainPattern& tp, td.data )
    {
        cout<<"Input:\n";
        for(int i = 0; i < tp.input.size(); i++)
            cout<<tp.input[i]<<" ";
        cout<<"Output:\n";
        for(int i = 0; i < tp.desired_output.size(); i++)
            cout<<tp.desired_output[i];
        cout<<endl<<endl;
    }
    */

    //Constructing perceptron
    vector<tuple<unsigned, ActivationFunction::Base*> > layers;
    layers.push_back(make_tuple(300,ActivationFunction::Linear::Instance())); //input  - no act. fcn
    layers.push_back(make_tuple(25, ActivationFunction::TanH::Instance()));   //hidden - tanh
    layers.push_back(make_tuple(16, ActivationFunction::TanH::Instance()));   //hidden - tanh
    layers.push_back(make_tuple(9,  ActivationFunction::TanH::Instance()));   //hidden - tanh
    layers.push_back(make_tuple(3,  ActivationFunction::Linear::Instance())); //output - linear
    NetPtr net_ptr = MultilayerPerceptron(layers);
    Net& net = *net_ptr;

    //Learning
    vector<Float> train_error_info; //MSE

    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.01;
    net[LmsAttributes::learningMomentum] = 0.1;
    net[RandomizeWeightsAttributes::min] = -0.1;
    net[RandomizeWeightsAttributes::max] = +0.1;
    net.run(RandomizeWeightsGaussRunner::Instance());

    const unsigned epochs = 100;
    progress_display progress(epochs);
    for(unsigned i = 1; i < epochs; ++i)
    {
        ++progress;
        td.shuffle();
        Lms::train(net, td);
        train_error_info.push_back(td.getMse());
    }

    //Plotting error graph
    try {
        Gnuplot gp_err("lines");
        gp_err.set_title("Error by epoch");
        gp_err.plot_x(train_error_info);

        cout<<"\nPress ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }
    
    return 0;
}

