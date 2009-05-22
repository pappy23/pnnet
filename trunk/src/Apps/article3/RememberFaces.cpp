
#include "pann.h"

using namespace pann;

Net& construct_net();

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

    Net& net = construct_net();

    Lms::init(net);
    net[LmsAttributes::learningRate] = 0.3;
    net[LmsAttributes::annealingTSC] = 100;
    Util::randomizeWeightsGauss(net, -0.2, 0.2);

    return 0;
}

Net& construct_net()
{
    const unsigned w = 92;
    const unsigned h = 112;

    vector<unsigned> layers;
    layers.push_back(w*h);

    return NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());
}

