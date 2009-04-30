//ConvolutionalNetwork.cpp

#include "ConvolutionalNetwork.h"

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"

using std::vector;
using namespace pann::OpenGlAttributes;

namespace pann
{
    namespace NetworkModel
    {
        Net&
        ConvolutionalNetworkDraft()
        {
            const unsigned total_layers = 5; //for OpenGL z-coordinate
            const unsigned input_w = 33;
            const unsigned input_h = 33;
            const unsigned fm_count = 6; //Feature maps in first convolution layer
            const unsigned fm_size_w = 15;
            const unsigned fm_size_h = 15;
            const unsigned window_w = 5;
            const unsigned window_h = 5;
            const unsigned overlap = 2; //window_h - overlap area
            const unsigned ss_range = 4; //2x2

            //OpenGL
            const Float distance_between_layers = 1000.0;
            const Float distance_between_neurons = 40.0;
            const Float distance_between_fms = 900.0;

            Net& net = *(new Net());

            typedef vector< vector<Neuron*> > plane;

            //Input layer 4x4
            plane input_layer;
            for(unsigned i = 0; i < input_h; ++i) //row
            {
                input_layer.push_back(vector<Neuron*>(input_w));
                for(unsigned j = 0; j < input_w; ++j) //column
                {
                    Neuron& n = *(new Neuron(0));
                    input_layer[i][j] = &n;
                    net.addInputNeuron(&n);

                    //OpenGL
                    n[color_r] = 0;
                    n[color_g] = 0;
                    n[color_b] = 255;
                    n[coord_x] = ( (1.0 - total_layers) / 2.0 + 1.0 ) * distance_between_layers;
                    n[coord_y] = ( Float(i) - Float(input_h) / 2.0 + 1.0 ) * distance_between_neurons;
                    n[coord_z] = ( Float(j) - Float(input_w) / 2.0 + 1.0 ) * distance_between_neurons;
                }
            }

            //N feature maps
            vector<plane> fm(fm_count); //convolution feature maps
            vector<plane> ss(fm_count); //subsampling planes

            /*
             * SS layer
             *
             * x1,x2,x3,x4 - inputs
             * y = f((x1+x2+x3+x4)/4 * W + bias)
             * f(x) = tanh(x)
             *
             */
            for(unsigned map_no = 0; map_no < fm_count; map_no++)
            {
                //Creating shared weights
                vector<vector<Weight*> > shared_w;
                for(unsigned i = 0; i < window_h; i++)
                {
                    shared_w.push_back(vector<Weight*>(window_w));
                    for(unsigned j = 0; j < window_w; j++)
                        shared_w[i][j] = new Weight(1);
                }
                //TODO shared bias for each feature map

                //Feature map
                for(unsigned i = 0; i < fm_size_h; ++i)
                {
                    fm[map_no].push_back(vector<Neuron*>(fm_size_w));
                    for(unsigned j = 0; j < fm_size_w; ++j)
                    {
                        Neuron* n = new Neuron(ActivationFunction::TanH::Instance());
                        fm[map_no][i][j] = n;

                        for(unsigned l = 0; l < window_h; l++)
                            for(unsigned m = 0; m < window_w; m++)
                                net.addConnection(input_layer[i*overlap+l][j*overlap+m], n, shared_w[l][m]);

                        //OpenGL
                        (*n)[color_r] = 255;
                        (*n)[color_g] = 0;
                        (*n)[color_b] = 0;
                        (*n)[coord_x] = ( (2.0 - total_layers) / 2.0 + 1.0 ) * distance_between_layers;
                        (*n)[coord_y] = ( Float(i) - Float(fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                        (*n)[coord_z] = ( Float(j) - Float(fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                            + ( Float(map_no) - Float(fm_count) / 2.0 + 0.5) * distance_between_fms;
                    }

                }

                //Subsampling plane
                for(unsigned i = 0; i < (fm_size_h / ss_range); ++i)
                {
                    ss[map_no].push_back( vector<Neuron*>( fm_size_w / ss_range ) );
                    for(unsigned j = 0; j < (fm_size_w / ss_range); ++j)
                    {
                        Neuron *n = new Neuron(ActivationFunction::TanH::Instance());
                        ss[map_no][i][j] = n;

                        Weight *w = new Weight(1);
                        for(unsigned l = 0; l < ss_range; ++l)
                            for(unsigned m = 0; m < ss_range; ++m)
                                net.addConnection(fm[map_no][i*ss_range + l][j*ss_range + m], n, w);

                        //OpenGL
                        (*n)[color_r] = 0;
                        (*n)[color_g] = 255;
                        (*n)[color_b] = 0;
                        (*n)[coord_x] = ( (3.0 - total_layers) / 2.0 + 1.0 ) * distance_between_layers;
                        (*n)[coord_y] = ( Float(i) - Float(fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                        (*n)[coord_z] = ( Float(j) - Float(fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
                            + ( Float(map_no) - Float(fm_count) / 2.0 + 0.5) * distance_between_fms;
                    }
                }
            }
            
            return net;
        };
    }; //NetworkModel

}; //pann

