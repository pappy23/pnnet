//ConvolutionalNetwork.cpp

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"
#include "Core/Random.h"
#include "NeuronFactories/PyramidalNeuron.h"

#include "ConvolutionalNetwork.h"

using namespace std;
using namespace boost;
using namespace pann::ConvolutionalNetworkTypes;

namespace pann
{
    NetPtr
    ConvolutionalNetwork(
        vector<unsigned> layers,
        Float connection_density,
        unsigned window_width,
        unsigned window_height,
        unsigned window_horiz_overlap,
        unsigned window_vert_overlap,
        TfPtr input_af,
        TfPtr conv_af,
        TfPtr ss_af,
        TfPtr output_af
        )
    {
        Model model = ConvolutionalNetworkModel(
                layers,
                connection_density,
                window_width,
                window_height,
                window_horiz_overlap,
                window_vert_overlap,
                input_af,
                conv_af,
                ss_af,
                output_af);

        NetPtr net(new Net());

        //Input neurons
        for(unsigned i = 0; i < model[0][0].size(); ++i)
            for(unsigned j = 0; j < model[0][0][0].size(); ++j)
                net->add_input_neuron(model[0][0][i][j]);

        return net;
    } //ConvolutionalNetwork

    Model
    ConvolutionalNetworkModel(vector<unsigned> _layers,
        Float _connection_density,
        unsigned _window_width,
        unsigned _window_height,
        unsigned _window_horiz_overlap,
        unsigned _window_vert_overlap,
        TfPtr _input_af,
        TfPtr _conv_af,
        TfPtr _ss_af,
        TfPtr _output_af
        )
    {
        /*
         * Comment
         * 1) checking for ambigous overlap values and if we got empty _layers
         * 2) _layers describes all convolutional planes counts
         *    Input layer is a layer with 1 plane - a sort of SS plane
         *    We add it to _layers
         * 3) Creating output layer - each plane with 1 neuron
         * 4) Main loop. Moving from output layer to input layer
         * 4.1) Create convolutional layer
         * 4.2) Create subsampling layer and connect it to already existent
         * convolutional. We don't create CONV layer for inputs
         * 4.3) Connect created SS layer to next CONV layer
         * 5) writing OpenGL information
         */

        //Check input data
        if(_layers.empty())
            throw Exception()<<"Planes count not specified\n";

        if(_window_height <= _window_vert_overlap
            || _window_width <= _window_horiz_overlap)
                throw Exception()<<"Overlap value is not correct\n";

        const unsigned ss_range = 2;

        //OpenGL
        //TODO: calculate opengl distances from layers count and so
        /*
        const Float distance_between_layers = 1000.0;
        const Float distance_between_neurons = 40.0;
        const Float distance_between_fms = 900.0;
        */
        /*
         * Each _layers[] contains information about planes count in corresponding
         * level. Level consists of two layers: convolutional and subsampling
         * Plus one input and one output layer
         */
        const unsigned total_layers = _layers.size() * 2;
        unsigned current_layer = total_layers - 1;


        Model model(total_layers);
        WeightPtr shared_bias;
        Net net;

        //Create output neurons
        //In output layer each plane consists from exactly one neuron
        for(unsigned i = 0; i < _layers.back(); ++i)
        {
            NeuronPtr neuron(NeuronFactory::PyramidalNeuron(_output_af));
            model[current_layer].push_back(Plane(1, Row(1, neuron)));
        }

        //Create convolutional-subsampling layers
        while(_layers.size() != 1)
        {
            _layers.pop_back();
            current_layer -= 2; //why 2? see code below

            bool is_input_layer = (_layers.size() == 1);

            const unsigned next_layer_plane_width
                = model[current_layer + 2][0][0].size();

            const unsigned next_layer_plane_height
                = model[current_layer + 2][0].size();

            const unsigned current_layer_ss_plane_width =
                next_layer_plane_width * (_window_width - _window_horiz_overlap) +
                    _window_horiz_overlap;

            const unsigned current_layer_ss_plane_height =
                next_layer_plane_height * (_window_height - _window_vert_overlap) +
                    _window_vert_overlap;

            const unsigned current_layer_conv_plane_width
                = current_layer_ss_plane_width * ss_range;

            const unsigned current_layer_conv_plane_height
                = current_layer_ss_plane_height * ss_range;

            //Constructing planes on current layer
            for(unsigned plane_no = 0; plane_no < _layers.back(); ++plane_no)
            {
                //Convolutional
                Plane conv_plane;
                shared_bias.reset(new Weight(1));
                if(!is_input_layer)
                {
                    for(unsigned i = 0; i < current_layer_conv_plane_height; ++i)
                    {
                        conv_plane.push_back(Row());
                        for(unsigned j = 0; j < current_layer_conv_plane_width; ++j)
                        {
                            NeuronPtr neuron(NeuronFactory::PyramidalNeuron(_conv_af, shared_bias));
                            conv_plane[i].push_back(neuron);
                        }
                    }
                }

                //Subsampling
                /*
                 * SS layer
                 *
                 * x1,x2,x3,x4 - inputs
                 * y = f((x1+x2+x3+x4) * W + bias)
                 * f(x) = tanh(x)
                 */
                Plane ss_plane;
                //According to LeCunn each plane in SS layer holds only 2
                //trainable parameters - shared weight and shared bias
                shared_bias.reset(new Weight(1));
                WeightPtr shared_ss_weight(new Weight(1));
                for(unsigned i = 0; i < current_layer_ss_plane_height; ++i)
                {
                    ss_plane.push_back(Row());
                    for(unsigned j = 0; j < current_layer_ss_plane_width; ++j)
                    {
                        NeuronPtr neuron;
                        if(is_input_layer)
                            neuron = NeuronFactory::PyramidalNeuron(_input_af);
                        else
                            neuron = NeuronFactory::PyramidalNeuron(_ss_af, shared_bias);

                        ss_plane[i].push_back(neuron);

                        //Connecting SS-neuron to corresponding convolutional
                        //neurons
                        if(!is_input_layer)
                            for(unsigned l = 0; l < ss_range; ++l)
                                for(unsigned m = 0; m < ss_range; ++m)
                                    net.add_connection(conv_plane \
                                            [i * ss_range + l] \
                                            [j * ss_range + m],
                                            neuron,
                                            shared_ss_weight);
                    }
                }

                //Connect current SS-layer to next CONV-layer
                //Phase 1: create shared weights
                vector<vector<WeightPtr> > shared_conv_weights(
                        _window_height,
                        vector<WeightPtr>(
                            _window_width,
                            WeightPtr((Weight*)0)
                        )
                );
                for(unsigned i = 0; i < _window_height; i++)
                    for(unsigned j = 0; j < _window_width; j++)
                        shared_conv_weights[i][j].reset(new Weight(1));

                //Phase 2: Build connection matrix for current plane
                /*
                 * Return part of square connection matrix like that:
                 *   1 2 3 4 5    <-to
                 * 1 X X X X X
                 * 2 X   X   X
                 * 3   X   X
                 * 4 X X   X X
                 * ^
                 * from
                 *
                 * For example above if called with _plane_no = 3, return FTFTF
                 */
                //Assume full connectivity by default
                vector<bool> conn_matrix(model[current_layer + 2].size(), true);
                //First plane always gets full connectivity
                if(plane_no != 0)
                {
                    bool all_false = true;
                    for(unsigned i = 0; i < conn_matrix.size(); ++i)
                    {
                        conn_matrix[i] = rand_coin(_connection_density);
                        if(conn_matrix[i])
                            all_false = false;
                    }
                    if(all_false)
                    {
                        conn_matrix[std::rand() % conn_matrix.size()] = true;
                        conn_matrix[std::rand() % conn_matrix.size()] = true;
                    }
                }

                //Phase 3: Actual connections
                //i iterates over next layer planes
                for(unsigned i = 0; i < model[current_layer + 2].size(); ++i)
                    if(conn_matrix[i])
                        for(unsigned j = 0; j < next_layer_plane_height; ++j)
                            for(unsigned k = 0; k < next_layer_plane_width; ++k)
                                for(unsigned l = 0; l < _window_height; ++l)
                                    for(unsigned m = 0; m < _window_width; ++m)
                                        net.add_connection(ss_plane \
                                        [j * (_window_height - _window_vert_overlap) + l] \
                                        [k * (_window_width - _window_horiz_overlap) + m],
                                        model[current_layer + 2][i][j][k],
                                        shared_conv_weights[l][m]);

                //Adding created CONV and SS planes to model
                model[current_layer + 1].push_back(ss_plane);
                if(!is_input_layer)
                    model[current_layer].push_back(conv_plane);

            } //planes in current layer
        } //while

        //OpenGL
        /*
        for(unsigned layer = 0; layer < model.size(); ++layer)
        {
            for(unsigned plane = 0; plane < model[layer].size(); ++plane)
            {
                for(unsigned i = 0; i < model[layer][plane].size(); ++i)
                {
                    for(unsigned j = 0; j < model[layer][plane][i].size(); ++j)
                    {
                        OpenGlAttributes& ogl = model[layer][plane][i][j]->get<OpenGlAttributes>();

                        //TODO Change colors for diferent types of neurons
                        ogl.r = 255;
                        ogl.g = 0;
                        ogl.b = 0;
                        ogl.x = static_cast<int>((
                                Float(layer) -
                                total_layers / 2.0 + 1.0
                                ) * distance_between_layers);
                        ogl.y = static_cast<int>((
                                Float(i) -
                                Float(model[layer][plane].size()) / 2.0 + 1.0
                                ) * distance_between_neurons);
                        ogl.z = static_cast<int>((
                                Float(j) -
                                Float(model[layer][plane][0].size()) / 2.0 + 1.0
                                ) * distance_between_neurons
                            + (
                                Float(plane) -
                                Float(model[layer].size()) / 2.0 + 0.5
                                ) * distance_between_fms);
                    }
                }
            }
        }
        */

        return model;
    } //ConvolutionalNetworkModel

}; //pann

