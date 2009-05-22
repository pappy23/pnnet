#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"
#include "gnuplot_i.hpp"

//convert -size 100x100 xc: +noise Random tmp1.pgm

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

    TrainData& train_data = (*DataGenerator::generateFromImageList(argv[1]));

    train_data.shuffle();
    TrainData test_data = DataGenerator::divide(train_data, 20);
    cout<<"Train data size: "<<train_data.data.size()
        <<"\nTest data size: "<<test_data.data.size()<<endl;

    //
    // Creating and initializing convolutional network
    //
    Net& net = NetworkModel::ConvolutionalNetworkDraft();
    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.3;
    net[LmsAttributes::annealingTSC] = 100;
    Util::randomizeWeightsGauss(net, -0.2, 0.2);
    //Util::randomizeWeightsAccordingToInputsCount(net);

    //
    // Test run
    //
    net.run(FeedforwardPropagationRunner::Instance());

    //
    // Training
    //
    vector<Float> train_error_info; //MSE
    const unsigned epochs = 1000;
    const unsigned stat = 100;
    //progress_display progress(epochs);
    for(unsigned i = 1; i < epochs; ++i)
    {
        //++progress;
        train_data.shuffle();
        Lms::train(net, train_data);
        train_error_info.push_back(train_data.getMse());

        cout<<"Train: "<<i<<" "<<train_error_info.back()<<endl;

        if(i % stat == 0)
        {
            //Saving Net
            Storage::save<Storage::bin_out>(net, lexical_cast<string>(i) + "_test_conv.bin");

            cout<<"Test: "<<Util::test(net, test_data)<<endl;
        }
    }

    //
    //Plotting error graph
    //
    /*
    try {
        Gnuplot gp_err("lines");
        gp_err.set_title("Error by epoch");
        gp_err.plot_x(train_error_info);

        cout<<"\nPress ENTER to exit...";
        cin.get();

    } catch(GnuplotException e) {
        cout << e.what() << endl;
    }
    */

    return 0;
}

