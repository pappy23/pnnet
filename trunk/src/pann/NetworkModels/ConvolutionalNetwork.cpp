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

            typedef vector<Neuron*> Row;
            typedef vector<Row> Plane;

            //Input layer 4x4
            Plane input_layer;
            for(unsigned i = 0; i < input_h; ++i) //row
            {
                input_layer.push_back(Row(input_w));
                for(unsigned j = 0; j < input_w; ++j) //column
                {
                    Neuron& n = *(new Neuron(0));
                    input_layer[i][j] = &n;
                    net.addInputNeuron(&n);

                    //OpenGL
                    n[color_r] = 0;
                    n[color_g] = 0;
                    n[color_b] = 255;
                    n[coord_x] = ( 1.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                    n[coord_y] = ( Float(i) - Float(input_h) / 2.0 + 1.0 ) * distance_between_neurons;
                    n[coord_z] = ( Float(j) - Float(input_w) / 2.0 + 1.0 ) * distance_between_neurons;
                }
            }

            Weight* shared_bias = 0;

            //C1, S1
            vector<Plane> c1(c1_fm_count); //convolution feature maps
            vector<Plane> s1(c1_fm_count); //subsampling planes

            for(unsigned map_no = 0; map_no < c1_fm_count; ++map_no)
            {
                //Creating shared weights
                shared_bias = new Weight(1, 0);
                vector<vector<Weight*> > shared_w;
                for(unsigned i = 0; i < c1_window_h; i++)
                {
                    shared_w.push_back(vector<Weight*>(c1_window_w));
                    for(unsigned j = 0; j < c1_window_w; j++)
                        shared_w[i][j] = new Weight(1);
                }

                //Feature map
                for(unsigned i = 0; i < c1_fm_size_h; ++i)
                {
                    c1[map_no].push_back(Row(c1_fm_size_w));
                    for(unsigned j = 0; j < c1_fm_size_w; ++j)
                    {
                        Neuron* n = new Neuron(ActivationFunction::TanH::Instance(), shared_bias);
                        shared_bias->usageCount++;
                        c1[map_no][i][j] = n;

                        for(unsigned l = 0; l < c1_window_h; l++)
                            for(unsigned m = 0; m < c1_window_w; m++)
                                net.addConnection(input_layer[i*c1_overlap+l][j*c1_overlap+m], n, shared_w[l][m]);

                        //OpenGL
                        (*n)[color_r] = 255;
                        (*n)[color_g] = 0;
                        (*n)[color_b] = 0;
                        (*n)[coord_x] = ( 2.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                        (*n)[coord_y] = ( Float(i) - Float(c1_fm_size_h) / 2.0 + 1.0 ) * distance_between_neurons;
                        (*n)[coord_z] = ( Float(j) - Float(c1_fm_size_w) / 2.0 + 1.0 ) * distance_between_neurons
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
                shared_bias = new Weight(1, 0);
                for(unsigned i = 0; i < (c1_fm_size_h / s1_range); ++i)
                {
                    s1[map_no].push_back(Row( c1_fm_size_w / s1_range ));
                    for(unsigned j = 0; j < (c1_fm_size_w / s1_range); ++j)
                    {
                        Neuron *n = new Neuron(ActivationFunction::TanH::Instance(), shared_bias);
                        shared_bias->usageCount++;
                        s1[map_no][i][j] = n;

                        Weight *w = new Weight(1);
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
                vector<vector<Weight*> > shared_w;
                shared_bias = new Weight(1, 0);
                for(unsigned i = 0; i < c2_window_h; i++)
                {
                    shared_w.push_back(vector<Weight*>(c2_window_w));
                    for(unsigned j = 0; j < c2_window_w; j++)
                        shared_w[i][j] = new Weight(1);
                }
                //TODO shared bias for each feature map

                //Feature map
                for(unsigned i = 0; i < c2_fm_size_h; ++i)
                {
                    c2[map_no].push_back(Row(c2_fm_size_w));
                    for(unsigned j = 0; j < c2_fm_size_w; ++j)
                    {
                        Neuron* n = new Neuron(ActivationFunction::TanH::Instance(), shared_bias);
                        shared_bias->usageCount++;
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
                f1[map_no] = new Neuron(ActivationFunction::TanH::Instance(), new Weight(1));
                //Subsampling plane
                shared_bias = new Weight(1, 0);
                for(unsigned i = 0; i < (c2_fm_size_h / s2_range); ++i)
                {
                    s2[map_no].push_back(Row( c2_fm_size_w / s2_range ));
                    for(unsigned j = 0; j < (c2_fm_size_w / s2_range); ++j)
                    {
                        Neuron *n = new Neuron(ActivationFunction::TanH::Instance(), shared_bias);
                        shared_bias->usageCount++;
                        s2[map_no][i][j] = n;

                        net.addConnection(n, f1[map_no], new Weight(1));

                        Weight *w = new Weight(1);
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
                output_layer[i] = new Neuron(ActivationFunction::TanH::Instance(), new Weight(1));
                Neuron &n = *output_layer[i];

                //OpenGL
                n[color_r] = 255;
                n[color_g] = 0;
                n[color_b] = 255;
                n[coord_x] = ( 7.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                n[coord_y] = 0;
                n[coord_z] = ( Float(i) - Float(c2_fm_count) / 2.0 + 1.0 ) * distance_between_neurons;
            }

            //Full connection layer
            for(unsigned i = 0; i < c2_fm_count; ++i)
            {
                Neuron &n = *f1[i];
                for(unsigned j = 0; j < output_neurons; ++j)
                    net.addConnection(&n, output_layer[j], new Weight(1));

                //OpenGL
                n[color_r] = 0;
                n[color_g] = 0;
                n[color_b] = 255;
                n[coord_x] = ( 6.0 - total_layers / 2.0 + 1.0 ) * distance_between_layers;
                n[coord_y] = 0;
                n[coord_z] = ( Float(i) - Float(c2_fm_count) / 2.0 + 1.0 ) * distance_between_neurons;
            }

            return net;
        };
    }; //NetworkModel

}; //pann

