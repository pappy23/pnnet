#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"
#include "gnuplot_i.hpp"

using namespace std;
using namespace pann;
using namespace boost;

/**
 * Argument - file with list of images
 */
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout<<"Usage: "<<argv[0]<<" <file_list>\n";
        return -1;
    }

    TrainData td;

    //
    // Reading data
    //
    ifstream ifs(argv[1]);
    unsigned total_images = 0,
             face_images = 0,
             notface_images = 0;
    while(!ifs.eof())
    {
        string fname;
        int is_face;
        ifs >> fname >> is_face;

        try {
            //cout<<"Reading "<<fname<<endl;
            total_images++;

            TrainPattern tp(35*35, 2);
            
            tp.input = Util::squash_copy(
                    DataGenerator::jpeg_gray2valarray(fname.c_str(), 35, 35),
                    -2.5,
                    +2.5
                );
            
            if(is_face == 1)
            {
                face_images++;
                tp.desired_output[0] = 1.5;
                tp.desired_output[1] = -1.5;
            } else {
                notface_images++;
                tp.desired_output[0] = -1.5;
                tp.desired_output[1] = 1.5;
            }
            td.data.push_back(tp);

        } catch(...) {
            //cout<<"Failed to read "<<fname<<endl;
        }
    }

    ifs.close();
    cout<<"Face / Not face / Total: "<<face_images<<" / "<<notface_images<<" / "<<total_images<<endl;

    //
    // Creating and initializing convolutional network
    //
    Net& net = NetworkModel::ConvolutionalNetworkDraft();
    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.01;
    net[LmsAttributes::learningMomentum] = 0.1;
    Util::randomizeWeightsGauss(net, -0.1, 0.1);
    //
    // Test run
    //
    net.run(FeedforwardPropagationRunner::Instance());

    //
    // Training
    //
    vector<Float> train_error_info; //MSE
    const unsigned epochs = 100;
    progress_display progress(epochs);
    for(unsigned i = 1; i < epochs; ++i)
    {
        ++progress;
        td.shuffle();
        Lms::train(net, td);
        train_error_info.push_back(td.getMse());
    }

    //
    //Plotting error graph
    //
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

