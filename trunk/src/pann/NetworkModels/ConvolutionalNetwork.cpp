//ConvolutionalNetwork.cpp

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"
#include "Core/Random.h"

#include "ConvolutionalNetwork.h"

using namespace std;
using namespace boost;
using namespace pann::ConvolutionalNetworkTypes;
using namespace pann::OpenGlAttributes;

namespace pann
{
    NetPtr
    ConvolutionalNetwork(vector<unsigned> _layers,
        Float _connection_density,
        unsigned _window_width,
        unsigned _window_height,
        unsigned _window_horiz_overlap,
        unsigned _window_vert_overlap,
        ActivationFunction::Base* _input_af,
        ActivationFunction::Base* _conv_af,
        ActivationFunction::Base* _ss_af,
        ActivationFunction::Base* _output_af
        )
    {
        Model model = ConvolutionalNetworkModel(
                _layers,
                _connection_density,
                _window_width,
                _window_height,
                _window_horiz_overlap,
                _window_vert_overlap,
                _input_af,
                _conv_af,
                _ss_af,
                _output_af);

        NetPtr net(new Net());

        //Input neurons
        for(unsigned i = 0; i < model[0][0].size(); ++i)
            for(unsigned j = 0; j < model[0][0][0].size(); ++j)
                net->addInputNeuron(model[0][0][i][j]);

        return net;
    } //ConvolutionalNetwork

    Model
    ConvolutionalNetworkModel(vector<unsigned> _layers,
        Float _connection_density,
        unsigned _window_width,
        unsigned _window_height,
        unsigned _window_horiz_overlap,
        unsigned _window_vert_overlap,
        ActivationFunction::Base* _input_af,
        ActivationFunction::Base* _conv_af,
        ActivationFunction::Base* _ss_af,
        ActivationFunction::Base* _output_af
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
        const Float distance_between_layers = 1000.0;
        const Float distance_between_neurons = 40.0;
        const Float distance_between_fms = 900.0;

        /*
         * Each _layers[] contains information about planes count in corresponding
         * level. Level consists of two layers: convolutional and subsampling
         * Plus one input and one output layer
         */
        const unsigned total_layers = _layers.size() * 2;
        unsigned current_layer = total_layers - 1;
        _layers.insert(_layers.begin(), 1); //For input layer

        Model model(total_layers);
        WeightPtr shared_bias;
        Net net;

        //Create output neurons
        //In output layer each plane consists from exactly one neuron
        for(unsigned i = 0; i < _layers.back(); ++i)
        {
            NeuronPtr neuron(new Neuron(_output_af));
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
                = current_layer_ss_plane_width * 2;

            const unsigned current_layer_conv_plane_height
                = current_layer_ss_plane_height * 2;

            //Constructing planes on current layer
            for(unsigned plane_no = 0; plane_no < _layers.back(); ++plane_no)
            {
                //Convolutional
                Plane conv_plane;
                shared_bias.reset(new Weight(1));
                if(!is_input_layer)
                    for(unsigned i = 0; i < current_layer_conv_plane_height; ++i)
                    {
                        conv_plane.push_back(Row());
                        for(unsigned j = 0; j < current_layer_conv_plane_width; ++j)
                        {
                            NeuronPtr neuron(new Neuron(_conv_af, shared_bias));
                            conv_plane[i].push_back(neuron);
                        }
                    }

                //Subsampling
                /*
                 * SS layer
                 *
                 * x1,x2,x3,x4 - inputs
                 * y = f((x1+x2+x3+x4)/4 * W + bias)
                 * f(x) = tanh(x)
                 */
                Plane ss_plane;
                shared_bias.reset(new Weight(1));
                for(unsigned i = 0; i < current_layer_ss_plane_height; ++i)
                {
                    ss_plane.push_back(Row());
                    for(unsigned j = 0; j < current_layer_ss_plane_width; ++j)
                    {
                        NeuronPtr neuron;
                        if(is_input_layer)
                            neuron.reset(new Neuron(_input_af));
                        else
                            neuron.reset(new Neuron(_ss_af, shared_bias));

                        ss_plane[i].push_back(neuron);

                        //Connecting SS-neuron to corresponding convolutional
                        //neurons
                        //TODO shared_weight is shared over connections to same
                        //TODO SS neuron or between all SS neurons in same plane?
                        WeightPtr shared_weight(new Weight(1));
                        if(!is_input_layer)
                            for(unsigned l = 0; l < ss_range; ++l)
                                for(unsigned m = 0; m < ss_range; ++m)
                                    net.addConnection(conv_plane \
                                            [i * ss_range + l] \
                                            [j * ss_range + m],
                                            neuron,
                                            shared_weight);
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
                if(plane_no != 0) //First plane always gets full connectivity
                {
                    bool all_false = true;
                    for(unsigned i = 0; i < conn_matrix.size(); ++i)
                    {
                        conn_matrix[i] = rand(_connection_density);
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
                                        net.addConnection(ss_plane \
                                [j * (_window_height - _window_vert_overlap) + l] \
                                [k * (_window_width - _window_horiz_overlap) + m], 
                                model[current_layer + 2][i][j][k],
                                shared_conv_weights[l][m]);

                //Adding created CONV and SS planes to model
                model[current_layer + 1].push_back(ss_plane);
                if(!is_input_layer)
                    model[current_layer].push_back(conv_plane);

            } //planes in current layer
        }

        //OpenGL
        for(unsigned layer = 0; layer < model.size(); ++layer)
            for(unsigned plane = 0; plane < model[layer].size(); ++plane)
                for(unsigned i = 0; i < model[layer][plane].size(); ++i)
                    for(unsigned j = 0; j < model[layer][plane][i].size(); ++j)
                    {
                        Neuron& n = *model[layer][plane][i][j];

                        //TODO Change colors for diferent types of neurons
                        n[color_r] = 255;
                        n[color_g] = 0;
                        n[color_b] = 0;
                        n[coord_x] = (
                                Float(layer) -
                                total_layers / 2.0 + 1.0
                                ) * distance_between_layers;
                        n[coord_y] = (
                                Float(i) -
                                Float(model[layer][plane].size()) / 2.0 + 1.0
                                ) * distance_between_neurons;
                        n[coord_z] = (
                                Float(j) -
                                Float(model[layer][plane][0].size()) / 2.0 + 1.0
                                ) * distance_between_neurons
                            + (
                                Float(plane) -
                                Float(model[layer].size()) / 2.0 + 0.5
                                ) * distance_between_fms;
                    }

        return model;
    } //ConvolutionalNetworkModel

}; //pann

