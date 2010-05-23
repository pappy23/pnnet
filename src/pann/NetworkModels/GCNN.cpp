//GCNN.cpp

#include <boost/multi_array.hpp>

#include "GCNN.h"
#include "Includes/Std.h"
#include "Core/Tf.h"
#include "Core/Weight.h"
#include "NeuronFactories/PyramidalNeuron.h"

using namespace std;

namespace pann
{
    typedef struct {
        int width;
        int height;
        int window_width;
        int window_height;
        TfPtr tf;
    } plane_data_t;

    typedef struct {
        boost::multi_array<NeuronPtr, 2> neurons;
        boost::multi_array<WeightPtr, 2> weights;
    } plane_t;

    typedef struct {
        vector<plane_t> planes;
        boost::multi_array<bool, 2> connection_matrix; //[from][to]
    } net_data_t;

    plane_t
    make_plane(plane_data_t plane_data, bool conv_plane = false)
    {
        plane_t plane;

        plane.neurons = boost::multi_array<NeuronPtr, 2>(boost::extents[plane_data.height][plane_data.width]);
        WeightPtr shared_bias(new Weight());

        for(int i = 0; i < plane_data.height; ++i)
            for(int j = 0; j < plane_data.width; ++j)
                plane.neurons[i][j] = NeuronFactory::PyramidalNeuron(plane_data.tf, shared_bias);

        plane.weights = boost::multi_array<WeightPtr, 2>(boost::extents[plane_data.window_height][plane_data.window_width]);
        WeightPtr shared_weight(new Weight());

        for(int i = 0; i < plane_data.window_height; ++i)
            for(int j = 0; j < plane_data.window_width; ++j)
                if(!conv_plane)
                    plane.weights[i][j] = WeightPtr(new Weight());
                else
                    plane.weights[i][j] = shared_weight;

        return plane;
    }; //make_plane

    void
    connect_planes(plane_t& prev_plane, plane_t& next_plane)
    {
        /**
         * Уместить `N` отрезков длинны `a` в одном отрезке длинны `A`,
         * обеспечив однородную плотность покрытия
         * Задача сводится к равномерному размещению N точек (центров масс отрезков a)
         * на отрезке (a/2; A - a/2) или на отрезке (0; A - a), если точки N - начала отрезков `a`
         * Отрезки размещаются с шагом (A - a) / (N - 1)
         */
        int vert_step = (prev_plane.neurons.size() - next_plane.weights.size()) / (next_plane.neurons.size() - 1);
        int horiz_step = (prev_plane.neurons[0].size() - next_plane.weights[0].size()) / (next_plane.neurons[0].size() - 1);

        Net fake_net;

        for(unsigned i = 0; i < next_plane.neurons.size(); ++i)
            for(unsigned j = 0; j < next_plane.neurons[0].size(); ++j)
                for(unsigned m = 0; m < next_plane.weights.size(); ++m)
                    for(unsigned n = 0; n < next_plane.weights[0].size(); ++n)
                        fake_net.add_connection(
                                prev_plane.neurons[i * vert_step + m][j * horiz_step + n],
                                next_plane.neurons[i][j],
                                next_plane.weights[m][n]);

    }; //connect_planes

    NetPtr
    make_net(const net_data_t& net_data)
    {
        for(unsigned i = 0; i < net_data.connection_matrix.size(); ++i)
           for(unsigned j = 0; j < net_data.connection_matrix[0].size(); ++j)
               if(net_data.connection_matrix[i][j])
                   connect_planes(planes[i], planes[j]);

        NetPtr net(new Net());
        for(unsigned i = 0; i < net_data.planes[0].neurons.size())
            for(unsigned j = 0; j < net_data.planes[0].neurons[0].size())
                net->add_input_neuron(net_data.planes[0].neurons[i][j]);

        return net;
    }; //make_net

    NetPtr
    make_convnet(
            vector<unsigned> layers,
            Float connection_density,
            unsigned window_height,
            unsigned window_width,
            unsigned window_vert_overlap,
            unsigned window_horiz_overlap,
            TfPtr input_tf,
            TfPtr ss_tf,
            TfPtr conv_tf,
            TfPtr output_tf)
    {
        assert(0.0 < connection_density);
        assert(connection_density <= 1.0);
        assert(window_height > window_vert_overlap);
        assert(window_width > window_horiz_overlap);
        assert(layers.size() > 0);
        for(unsigned i = 0; i < layers.size(); ++i)
            assert(layers[i] > 0);

        unsigned ss_range = 2;

        /*
        OpenGL
        TODO: calculate opengl distances from layers count and so
        */
        distance_between_layers = 1000.0;
        distance_between_neurons = 40.0;
        distance_between_fms = 900.0;

        /*
        Each layers[] contains information about planes count in corresponding
        level. Level consists of two layers: convolutional and subsampling
        Plus one input and one output layer
        */
        unsigned total_layers = layers.size() * 2;
        unsigned current_layer = total_layers - 1;
        layers.insert(layers.begin(), 1); //For input layer

        model = [[] for x in range(total_layers)]
        net = Net()

                   """
                   Create output neurons
                   In output layer each plane consists from exactly one neuron
                   """
                   for i in range(layers[-1]):
                       model[current_layer].append([[PyramidalNeuron(output_tf)]])

                   """
                   Create convolutional-subsampling layers
                   """
                   while len(layers) != 1:
                       layers.pop()
                       current_layer -= 2 #why 2? see code below

                       is_input_layer = (len(layers) == 1)
                       next_layer_plane_width = len(model[current_layer + 2][0][0])
                       next_layer_plane_height = len(model[current_layer + 2][0])
                       current_layer_ss_plane_width = next_layer_plane_width * (window_width - window_horiz_overlap) + window_horiz_overlap;
                       current_layer_ss_plane_height = next_layer_plane_height * (window_height - window_vert_overlap) + window_vert_overlap;
                       current_layer_conv_plane_width = current_layer_ss_plane_width * ss_range;
                       current_layer_conv_plane_height = current_layer_ss_plane_height * ss_range;

                       #Constructing planes on current layer
                       for plane_no in range(layers[-1]):
                           conv_plane = []
                           shared_bias = Weight(1.0)
                           if not is_input_layer:
                               for i in range(current_layer_conv_plane_height):
                                   conv_plane.append([])
                                   for j in range(current_layer_conv_plane_width):
                                       neuron = PyramidalNeuron(conv_tf)
                                       net.connect(BiasNeuron(), neuron, shared_bias)
                                       conv_plane[i].append(neuron)

                           #Subsampling
                           """
                           SS layer

                           x1,x2,x3,x4 - inputs
                           y = f((x1+x2+x3+x4) * W + bias)
                           f(x) = tanh(x)

                           According to LeCunn each plane in SS layer holds only 2
                           trainable parameters - shared weight and shared bias
                           """
                           ss_plane = []
                           shared_bias = Weight(1.0)
                           shared_ss_weight = Weight(1.0)
                           for i in range(current_layer_ss_plane_height):
                               ss_plane.append([])
                               for j in range(current_layer_ss_plane_width):
                                   if is_input_layer:
                                       neuron = PyramidalNeuron(input_tf)
                                   else:
                                       neuron = PyramidalNeuron(ss_tf)
                                       net.connect(BiasNeuron(), neuron, shared_bias)
                                   ss_plane[i].append(neuron)
                                   #Connecting SS-neuron to corresponding convolutional neurons
                                   if not is_input_layer:
                                       for l in range(ss_range):
                                           for m in range(ss_range):
                                               net.connect(conv_plane[i * ss_range + l][j * ss_range + m], neuron, shared_ss_weight)

                           #Adding created CONV and SS planes to model
                           model[current_layer + 1].append(ss_plane)
                           if not is_input_layer:
                               model[current_layer].append(conv_plane)

                   #For entire topology - connect CONV-SHARE pairs to each other, layer to layer
                   for d in range(0, len(model) / 2 + 2, 2):
                       next_layer = model[d+1]
                       prev_layer = model[d]
                       next_layer_plane_width  = len(next_layer[0][0])
                       next_layer_plane_height = len(next_layer[0])
                       prev_layer_plane_width  = len(prev_layer[0])
                       prev_layer_plane_height = len(prev_layer)
                       for next_layer_plane in next_layer:
                           #Phase 2: create shared weights
                           shared_conv_weights = [ [Weight(1.0) for j in range(window_width)] for i in range(window_height) ]
                           #Phase 3: Actual connections
                           for prev_layer_plane in prev_layer:
                               if prev_layer_plane is prev_layer[0] or random.random() < connection_density: #FIXME
                                   for i in range(next_layer_plane_height):
                                       for j in range(next_layer_plane_width):
                                           for k in range(window_height):
                                               for l in range(window_width):
                                                   net.connect(prev_layer_plane
                                                       [i * (window_height - window_vert_overlap) + k]
                                                       [j * (window_width - window_horiz_overlap) + l],
                                                       next_layer_plane[i][j], shared_conv_weights[k][l])

                   #OpenGL
                   for layer_no in range(len(model)):
                       for plane_no in range(len(model[layer_no])):
                           for row_no in range(len(model[layer_no][plane_no])):
                               for col_no in range(len(model[layer_no][plane_no][row_no])):
                                   model[layer_no][plane_no][row_no][col_no].opengl_attributes = Attributes()
                                   ogl = model[layer_no][plane_no][row_no][col_no].opengl_attributes

                                   #TODO Change colors for diferent types of neurons
                                   ogl.r = 255;
                                   ogl.g = 0;
                                   ogl.b = 0;
                                   ogl.x = (layer_no - total_layers / 2.0 + 1.0) * distance_between_layers
                                   ogl.y = (row_no - len(model[layer_no][plane_no]) / 2.0 + 1.0) * distance_between_neurons
                                   ogl.z = (col_no - len(model[layer_no][plane_no][0]) / 2.0 + 1.0) * distance_between_neurons
                                   + (plane_no - len(model[layer_no]) / 2.0 + 0.5) * distance_between_fms

                   return model
    }; //make_convnet

}; //pann

