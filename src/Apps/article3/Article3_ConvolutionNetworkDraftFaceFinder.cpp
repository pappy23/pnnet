#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"
#include "gnuplot_i.hpp"

//convert -size 100x100 xc: +noise Random tmp1.pgm

using namespace std;
using namespace pann;
using namespace boost;
using namespace boost::assign;


NetPtr
ConvolutionalNetwork(vector<unsigned> _planes,
        unsigned _window_width  = 5,
        unsigned _window_height = 5,
        unsigned _window_horiz_overlap = 3,
        unsigned _window_vert_overlap  = 3)
{
    //TODO: OpenGL, shared weights
    typedef vector<NeuronPtr> Row;
    typedef vector<Row> Plane;
    typedef vector<Plane> Layer;

    //Check input data
    if(_planes.empty())
        throw Exception()<<"Planes count not specified\n";

    if(
        _window_height <= _window_vert_overlap
        or
        _window_width <= _window_horiz_overlap
    )
        throw Exception()<<"Overlap value is not correct\n";

    /*
     * Each _plane[] contains infirmation about planes number in corresponding
     * level. Level consists of two layers: convolutional and subsampling
     * Plus one input and one output layer
     */
    const unsigned total_layers = 1 + _planes.size() * 2 + 1;
    unsigned current_layer = total_layers - 1;
    vector<Layer> model(total_layers);

    //Create output neurons
    //In output layer each plane consists from exactly one neuron
    for(unsigned i = 0; i < _planes.back(); ++i)
    {
        NeuronPtr neuron(new Neuron(ActivationFunction::TanH::Instance())); //FIXME
        Row row(1, neuron);
        Plane plane(1, row);
        model[current_layer].push_back(plane);
    }
    _planes.pop_back();
    current_layer--;

    //TODO: generate connection matrixes for all layer couples
    //full mesh for last and first layer and random connections for internal layers

    //Create convolutional-subsampling layers
    while(!_planes.empty())
    {
        for(unsigned i = 0; i < _planes.back(); ++i)
        {
            const unsigned next_layer_plane_width  = model[current_layer + 1][0][0].size;
            const unsigned next_layer_plane_height = model[current_layer + 1][0].size();
            const unsigned current_layer_conv_plane_width =
                next_layer_plane_width * (_window_width - _window_horiz_overlap_) +
                    _window_horiz_overlap;
            const unsigned current_layer_conv_plane_height =
                next_layer_plane_height * (_window_height - _window_vert_overlap_) +
                    _window_vert_overlap;
            const unsigned current_layer_ss_plane_width = current_layer_conv_plane_width / 2; //FIXME: oddity check
            const unsigned current_layer_ss_plane_height = current_layer_conv_plane_height / 2;

            //Convolutional
            Plane conv_plane();
            Plane ss_plane();
        }
        _planes.pop_back();
    }


    //Create last, input, layer


    //Debug
    for(unsigned i = 0; i < model.size(); ++i)
    {
        Debug()<<"Planes: "<<model[i].size()<<": ";
        for(unsigned j = 0; j < model[i].size(); ++j)
            Debug()<<model[i][j].size()<<"x"<<model[i][j][0].size()<<" ";
        Debug()<<"\n";
    }

    NetPtr net(new Net());
    return net;
}

Net& ConvolutionalNetworkDraft();

/**
 * Argument - file with list of images
 */
int main(int argc, char* argv[])
{
    vector<unsigned> planes;
    planes += 3,5;
    NetPtr net = ConvolutionalNetwork(planes);

    Storage::save<Storage::bin_out>(*net, "test_conv.bin");

/*
    if(argc != 2)
    {
        cout<<"Usage: "<<argv[0]<<" <file_list>\n";
        return -1;
    }

    cout<<"Reading data\n";
    TrainData& train_data = (*DataGenerator::generateFromImageList(argv[1]));

    train_data.shuffle();
    TrainData test_data = DataGenerator::divide(train_data, 20);
    cout<<"Train data size: "<<train_data.data.size()
        <<"\nTest data size: "<<test_data.data.size()<<endl;

    //
    // Creating and initializing convolutional network
    //
    Net& net = ConvolutionalNetworkDraft();
    Storage::save<Storage::bin_out>(net, "init_test_conv.bin");
    cout<<"Net ready\n";
    Lms::init(net);
    cout<<"Init ok\n";
    net[LmsAttributes::learningRate] = 0.3;
    net[LmsAttributes::annealingTSC] = 100;
    net[RandomizeWeightsAttributes::min] = -0.2;
    net[RandomizeWeightsAttributes::max] = +0.2;
    net.run(RandomizeWeightsGaussRunner::Instance());
    cout<<"Weights randomized\n";

    //
    // Test run
    //
    net.run(FeedforwardPropagationRunner::Instance());
    cout<<"Test run - OK\n";

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
*/
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

Net&
ConvolutionalNetworkDraft()
{
    using namespace pann::OpenGlAttributes;

    const unsigned input_w = 35;
    const unsigned input_h = 35;
    const unsigned c1_fm_count = 8; //Feature maps in first convolution layer
    const unsigned c1_fm_size_w = 16;
    const unsigned c1_fm_size_h = 16;
    const unsigned c1_window_w = 5;
    const unsigned c1_window_h = 5;
    const unsigned c1_overlap = 2; //window_h - overlap area
    const unsigned s1_range = 2; //2x2

    const unsigned c2_fm_count = 20;
    const unsigned c2_fm_size_w = 6; 
    const unsigned c2_fm_size_h = 6;
    const unsigned c2_window_w = 3;
    const unsigned c2_window_h = 3;
    const unsigned c2_overlap = 1;
    const unsigned s2_range = 2;
    const unsigned output_neurons = 2;
    //C2 -> S1 connection matrix
    //When no connection - fill with 99
    const unsigned connection_matrix[][c1_fm_count] = {
        {0, 1, 2, 3, 4, 5, 6, 7}, //0
        {99,1, 2, 3, 4, 5, 6, 7}, //1
        {0,99, 2, 3, 4, 5, 6, 7}, //2
        {0, 1,99, 3, 4, 5, 6, 7}, //3
        {0, 1, 2,99, 4, 5, 6, 7}, //4
        {0, 1, 2, 3,99, 5, 6, 7}, //5
        {0, 1, 2, 3, 4,99, 6, 7}, //6
        {0, 1, 2, 3, 4, 5,99, 7}, //7
        {0, 1, 2, 3, 4, 5, 6,99}, //8
        {99,99,2, 3, 4, 5, 6, 7}, //9
        {0, 1,99,99, 4,99, 6, 7}, //10
        {0, 1, 2, 3, 4, 5, 6, 7}, //11
        {99,1, 2,99, 4,99, 6, 7}, //12
        {0, 1,99, 3, 4, 5,99, 7}, //13
        {99,1,99, 3, 4,99, 6, 7}, //14
        {0,99, 2,99, 4, 5, 6, 7}, //15
        {0, 1,99, 3,99, 5, 6, 7}, //16
        {0, 1,99, 3, 4, 5, 6,99}, //17
        {0, 1, 2, 3, 4, 5, 6, 7}, //18
        {0, 1, 2, 3,99, 5, 6, 7}, //19
        {0,99, 2, 3, 4,99, 6, 7}, //20
        {99,1, 2,99, 4, 5, 6, 7}, //21
        {0, 1,99, 3, 4,99, 6, 7}, //22
        {0,99, 2, 3, 4, 5,99, 7}, //23
        {99, 1, 2,99, 4, 5,99, 7}, //24
        {99,99, 2,99, 4, 5,99,99}, //25
        {99,1,99, 3,99, 5,99, 7}, //26
        {0, 1,99, 3,99, 5,99,99}, //27
        {99,99,99,99,99,5, 6, 7}, //28
        {0, 1, 2,99,99,99,99,99}, //29
    };

    //OpenGL
    const unsigned total_layers = 7; //for OpenGL z-coordinate
    const Float distance_between_layers = 1000.0;
    const Float distance_between_neurons = 40.0;
    const Float distance_between_fms = 900.0;

    Net& net = *(new Net());

    typedef vector<shared_ptr<Neuron> > Row;
    typedef vector<Row> Plane;

    //Input layer 4x4
    Plane input_layer;
    for(unsigned i = 0; i < input_h; ++i) //row
    {
        input_layer.push_back(Row(input_w));
        for(unsigned j = 0; j < input_w; ++j) //column
        {
            shared_ptr<Neuron> n(new Neuron(ActivationFunction::Linear::Instance()));
            input_layer[i][j] = n;
            net.addInputNeuron(n);

            //OpenGL
            n->at(color_r) = 0;
            n->at(color_g) = 0;
            n->at(color_b) = 255;
            n->at(coord_x) = ( 1.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
            n->at(coord_y) = ( Float(i) - Float(input_h) / 2.0 + 1.0 ) * distance_between_neurons;
            n->at(coord_z) = ( Float(j) - Float(input_w) / 2.0 + 1.0 ) * distance_between_neurons;
        }
    }

    shared_ptr<Weight> shared_bias;

    //C1, S1
    vector<Plane> c1(c1_fm_count); //convolution feature maps
    vector<Plane> s1(c1_fm_count); //subsampling planes

    for(unsigned map_no = 0; map_no < c1_fm_count; ++map_no)
    {
        //Creating shared weights
        shared_bias.reset(new Weight(1));
        vector<vector<shared_ptr<Weight> > > shared_w;
        for(unsigned i = 0; i < c1_window_h; i++)
        {
            shared_w.push_back(vector<shared_ptr<Weight> >(c1_window_w));
            for(unsigned j = 0; j < c1_window_w; j++)
                shared_w[i][j] = shared_ptr<Weight>(new Weight(1));
        }

        //Feature map
        for(unsigned i = 0; i < c1_fm_size_h; ++i)
        {
            c1[map_no].push_back(Row(c1_fm_size_w));
            for(unsigned j = 0; j < c1_fm_size_w; ++j)
            {
                shared_ptr<Neuron> n(new Neuron(ActivationFunction::TanH::Instance(), shared_bias));
                c1[map_no][i][j] = n;

                for(unsigned l = 0; l < c1_window_h; l++)
                    for(unsigned m = 0; m < c1_window_w; m++)
                        net.addConnection(input_layer[i*c1_overlap+l][j*c1_overlap+m], n, shared_w[l][m]);

                //OpenGL
                n->at(color_r) = 255;
                n->at(color_g) = 0;
                n->at(color_b) = 0;
                n->at(coord_x) = ( 2.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                n->at(coord_y) = ( Float(i) - Float(c1_fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                n->at(coord_z) = ( Float(j) - Float(c1_fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                    + ( Float(map_no) - Float(c1_fm_count) / 2.0 + 0.5) * distance_between_fms;
            }

        }

        //Subsampling plane
        /*
         * SS layer
         *
         * x1,x2,x3,x4 - inputs
         * y = f((x1+x2+x3+x4)/4 * W + bias)
         * f(x) = tanh(x)
         *
         */
        shared_bias.reset(new Weight(1));
        for(unsigned i = 0; i < (c1_fm_size_h / s1_range); ++i)
        {
            s1[map_no].push_back(Row( c1_fm_size_w / s1_range ));
            for(unsigned j = 0; j < (c1_fm_size_w / s1_range); ++j)
            {
                shared_ptr<Neuron> n(new Neuron(ActivationFunction::TanH::Instance(), shared_bias));
                s1[map_no][i][j] = n;

                shared_ptr<Weight> w(new Weight(1));
                for(unsigned l = 0; l < s1_range; ++l)
                    for(unsigned m = 0; m < s1_range; ++m)
                        net.addConnection(c1[map_no][i*s1_range + l][j*s1_range + m], n, w);

                //OpenGL
                (*n)[color_r] = 255;
                (*n)[color_g] = 255;
                (*n)[color_b] = 0;
                (*n)[coord_x] = ( 3.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                (*n)[coord_y] = ( Float(i) - Float(c1_fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                (*n)[coord_z] = ( Float(j) - Float(c1_fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                    + ( Float(map_no) - Float(c1_fm_count) / 2.0 + 0.5) * distance_between_fms;
            }
        }
    }
    
    //C2, S2
    vector<Plane> c2(c2_fm_count); //convolution feature maps
    vector<Plane> s2(c2_fm_count); //subsampling planes
    Row f1(c2_fm_count);

    for(unsigned map_no = 0; map_no < c2_fm_count; ++map_no)
    {
        //Creating shared weights
        vector<vector<shared_ptr<Weight> > > shared_w;
        shared_bias.reset(new Weight(1));
        for(unsigned i = 0; i < c2_window_h; i++)
        {
            shared_w.push_back(vector<shared_ptr<Weight> >(c2_window_w));
            for(unsigned j = 0; j < c2_window_w; j++)
                shared_w[i][j] = shared_ptr<Weight>(new Weight(1));
        }
        //TODO shared bias for each feature map

        //Feature map
        for(unsigned i = 0; i < c2_fm_size_h; ++i)
        {
            c2[map_no].push_back(Row(c2_fm_size_w));
            for(unsigned j = 0; j < c2_fm_size_w; ++j)
            {
                shared_ptr<Neuron> n(new Neuron(ActivationFunction::TanH::Instance(), shared_bias));
                c2[map_no][i][j] = n;

                for(unsigned l = 0; l < c2_window_h; ++l)
                    for(unsigned m = 0; m < c2_window_w; ++m)
                        for(unsigned k = 0; k < c1_fm_count; ++k)
                            if(connection_matrix[i][k] != 99)
                                net.addConnection(s1[k][i*c2_overlap+l][j*c2_overlap+m], n, shared_w[l][m]);

                //OpenGL
                (*n)[color_r] = 255;
                (*n)[color_g] = 0;
                (*n)[color_b] = 0;
                (*n)[coord_x] = ( 4.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                (*n)[coord_y] = ( Float(i) - Float(c2_fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                (*n)[coord_z] = ( Float(j) - Float(c2_fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                    + ( Float(map_no) - Float(c2_fm_count) / 2.0 + 0.5) * distance_between_fms;
            }

        }

        //Full mesh layer
        f1[map_no] = shared_ptr<Neuron>(
                new Neuron(ActivationFunction::TanH::Instance(),
                shared_ptr<Weight>(new Weight(1)))
            );
        //Subsampling plane
        shared_bias.reset(new Weight(1));
        for(unsigned i = 0; i < (c2_fm_size_h / s2_range); ++i)
        {
            s2[map_no].push_back(Row( c2_fm_size_w / s2_range ));
            for(unsigned j = 0; j < (c2_fm_size_w / s2_range); ++j)
            {
                shared_ptr<Neuron> n(new Neuron(ActivationFunction::TanH::Instance(), shared_bias));
                s2[map_no][i][j] = n;

                net.addConnection(n, f1[map_no], shared_ptr<Weight>(new Weight(1)));

                shared_ptr<Weight> w(new Weight(1));
                for(unsigned l = 0; l < s2_range; ++l)
                    for(unsigned m = 0; m < s2_range; ++m)
                        net.addConnection(c2[map_no][i*s2_range + l][j*s2_range + m], n, w);

                //OpenGL
                (*n)[color_r] = 255;
                (*n)[color_g] = 255;
                (*n)[color_b] = 0;
                (*n)[coord_x] = ( 5.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                (*n)[coord_y] = ( Float(i) - Float(c2_fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                (*n)[coord_z] = ( Float(j) - Float(c2_fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                    + ( Float(map_no) - Float(c2_fm_count) / 2.0 + 0.5) * distance_between_fms;
            }
        }
    } 

    //Last layer
    Row output_layer(output_neurons);
    for(unsigned i = 0; i < output_neurons; ++i)
    {
        shared_ptr<Neuron> n(
                new Neuron(ActivationFunction::TanH::Instance(), shared_ptr<Weight>(new Weight(1)))
            );

        output_layer[i] = n;

        //OpenGL
        n->at(color_r) = 255;
        n->at(color_g) = 0;
        n->at(color_b) = 255;
        n->at(coord_x) = ( 7.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
        n->at(coord_y) = 0;
        n->at(coord_z) = ( Float(i) - Float(c2_fm_count) / 2.0 + 1.0 ) * distance_between_neurons;
    }

    //Full connection layer
    for(unsigned i = 0; i < c2_fm_count; ++i)
    {
        shared_ptr<Neuron> n = f1[i];
        for(unsigned j = 0; j < output_neurons; ++j)
            net.addConnection(n, output_layer[j], shared_ptr<Weight>(new Weight(1)));

        //OpenGL
        n->at(color_r) = 0;
        n->at(color_g) = 0;
        n->at(color_b) = 255;
        n->at(coord_x) = ( 6.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
        n->at(coord_y) = 0;
        n->at(coord_z) = ( Float(i) - Float(c2_fm_count) / 2.0 + 1.0 ) * distance_between_neurons;
    }

    return net;
};

