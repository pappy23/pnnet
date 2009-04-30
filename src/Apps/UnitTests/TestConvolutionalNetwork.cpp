#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    Net& net = NetworkModel::ConvolutionalNetworkDraft();
    net.run(FeedforwardPropagationRunner::Instance());

    //Constructing perceptron
    /*
    vector<unsigned> layers;
    layers.push_back(1000);
    layers.push_back(1000);
    layers.push_back(1000);
    layers.push_back(1000);
    layers.push_back(1000);
    Net& net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());
    */

    Storage::save<Storage::txt_out>(net, "test_conv.bin");

    return 0;
}

