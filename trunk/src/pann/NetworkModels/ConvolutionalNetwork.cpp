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
            Net& net = *(new Net());

            typedef vector< vector<Neuron*> > plane;

            const unsigned input_w = 33;
            const unsigned input_h = 33;

            //Input layer 33x33
            plane input_layer(input_h);
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
                    n[coord_x] = ( -5.0 / 2.0 + 1.0 ) * 100;
                    n[coord_y] = ( Float(i) - Float(input_h) / 2.0 + 1.0 ) * 40.0;
                    n[coord_z] = ( Float(j) - Float(input_w) / 2.0 + 1.0 ) * 40.0;
                }
            }

            std::cout<<"marker\n";
            std::cout.flush();

            const unsigned fm_count = 6;
            //N feature maps
            vector<plane> fm(fm_count);
            for(unsigned map_no = 0; map_no < fm_count; map_no++)
            {
                const unsigned window_w = 5;
                const unsigned window_h = 5;

                //window size = 5x5, overlap = 3
                vector<vector<Weight*> > shared_w(window_h);
                for(unsigned i = 0; i < window_h; i++)
                {
                    shared_w.push_back(vector<Weight*>(window_w));
                    for(unsigned j = 0; j < window_w; j++)
                        shared_w[i][j] = new Weight(1);
                }

                const unsigned fm_size_w = 28;
                const unsigned fm_size_h = 28;

                //Feature map
                for(unsigned i = 0; i < fm_size_h; ++i)
                {
                    fm[map_no].push_back(vector<Neuron*>(fm_size_h));
                    for(unsigned j = 0; j < fm_size_w; ++j)
                    {
                        const unsigned overlap = 2;
                        Neuron* n = new Neuron(ActivationFunction::TanH::Instance());
                        fm[map_no][i][j] = n;
                        for(unsigned l = 0; l < window_h; l++)
                            for(unsigned m = 0; m < window_w; m++)
                                net.addConnection(input_layer[i*overlap+l][j*overlap+m], n, shared_w[l][m]);

                        //OpenGL
                        (*n)[color_r] = 255;
                        (*n)[color_g] = 0;
                        (*n)[color_b] = 0;
                        (*n)[coord_x] = ( (1.0 - 5.0) / 2.0 + 1.0 ) * 100;
                        (*n)[coord_y] = ( Float(i) - Float(fm_size_h) / 2.0 + 1.0 ) * 40.0 + (map_no - 6) * 100;
                        (*n)[coord_z] = ( Float(j) - Float(fm_size_w) / 2.0 + 1.0 ) * 40.0;
                    }

                }
            }
            
            return net;
        };
    };

}; //pann

