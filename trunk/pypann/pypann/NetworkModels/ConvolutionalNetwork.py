#
# ConvolutionalNetwork
#

import random
from ..Core import *
from ..TF import Tanh
from ..Neurons import PyramidalNeuron
from ..Neurons import BiasNeuron

def convolutional_network(
        layers,
        connection_density = 0.5,
        window_height = 5,
        window_width = 5,
        window_vert_overlap = 3,
        window_horiz_overlap = 3,
        input_tf = Tanh,
        conv_tf = Tanh,
        ss_tf = Tanh,
        output_tf = Tanh):

    model = convolutional_network_model(
        layers,
        connection_density,
        window_height,
        window_width,
        window_vert_overlap,
        window_horiz_overlap,
        input_tf,
        conv_tf,
        ss_tf,
        output_tf
        )

    net = Net()

    #Input neurons
    for row in model[0][0]:
        for neuron in row:
            net.add_input_neuron(neuron)

    #Trace
    for layer_no in range(len(model)):
        for plane_no in range(len(model[layer_no])):
            for row_no in range(len(model[layer_no][plane_no])):
                for col_no in range(len(model[layer_no][plane_no][row_no])):
                    model[layer_no][plane_no][row_no][col_no].topology_info = Attributes()
                    model[layer_no][plane_no][row_no][col_no].topology_info.layer = layer_no
                    model[layer_no][plane_no][row_no][col_no].topology_info.plane = plane_no
                    model[layer_no][plane_no][row_no][col_no].topology_info.row = row_no
                    model[layer_no][plane_no][row_no][col_no].topology_info.col = col_no

    return net

def convolutional_network_model(
        layers,
        connection_density,
        window_height,
        window_width,
        window_vert_overlap,
        window_horiz_overlap,
        input_tf,
        conv_tf,
        ss_tf,
        output_tf):
    """
    Comment
    1) checking for ambigous overlap values and if we got empty _layers
    2) layers describes all convolutional planes counts
       Input layer is a layer with 1 plane - a sort of SS plane
       We add it to layers
    3) Creating output layer - each plane with 1 neuron
    4) Main loop. Moving from output layer to input layer
    4.1) Create convolutional layer
    4.2) Create subsampling layer and connect it to already existent
    convolutional. We don't create CONV layer for inputs
    4.3) Connect created SS layer to next CONV layer
    5) writing OpenGL information
    """

    assert(isinstance(layers, list))
    assert(isinstance(connection_density, float))
    assert(isinstance(window_height, int))
    assert(isinstance(window_width, int))
    assert(isinstance(window_horiz_overlap, int))
    assert(isinstance(window_vert_overlap, int))
    assert(isinstance(input_tf,  TF.TF))
    assert(isinstance(conv_tf,   TF.TF))
    assert(isinstance(ss_tf,     TF.TF))
    assert(isinstance(output_tf, TF.TF))
    assert(window_height > window_vert_overlap)
    assert(window_width > window_horiz_overlap)
    assert(len(layers) > 0)
    for planes_count in layers:
        assert(isinstance(planes_count, int))
        assert(planes_count > 0)

    ss_range = 2

    """
    OpenGL
    TODO: calculate opengl distances from layers count and so
    """
    distance_between_layers = 1000.0;
    distance_between_neurons = 40.0;
    distance_between_fms = 900.0;

    """
    Each layers[] contains information about planes count in corresponding
    level. Level consists of two layers: convolutional and subsampling
    Plus one input and one output layer
    """
    total_layers = len(layers) * 2
    current_layer = total_layers - 1
    layers.insert(0, 1); #For input layer

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
        """
        model[d] - prev layer (SS)
        model[d+1] - next layer (CONV)
        We should connect them
        """
##TODO!!!!
        #Connect current SS-layer to next CONV-layer
        #Phase 1: create shared weights
        shared_conv_weights = [ [Weight(1.0) for j in range(window_width)] for i in range(window_height) ]

        #Phase 2: Build connection matrix for current plane
        """
        Return part of square connection matrix like that:
          1 2 3 4 5    <-to
        1 X X X X X
        2 X   X   X
        3   X   X
        4 X X   X X
        ^
        from

        For example above if called with plane_no = 3, return FTFTF
        """
        #Assume full connectivity by default
        conn_matrix = [True] * len(model[current_layer + 2])

        #First plane always gets full connectivity
        #FIXME
        #if plane_no:
        #    all_false = True
        #    for i in range(len(conn_matrix)):
        #        conn_matrix[i] = random.triangular(0.0, 1.0, connection_density)
        #        if conn_matrix[i]:
        #            all_false = False
        #    if all_false:
        #        conn_matrix[round(random.uniform(0, len(conn_matrix)))] = True;
        #        conn_matrix[round(random.uniform(0, len(conn_matrix)))] = True;


        #Phase 3: Actual connections
        #i iterates over next layer planes
        for i in range(len(model[current_layer + 2])):
            if conn_matrix[i]:
                for j in range(next_layer_plane_height):
                    for k in range(next_layer_plane_width):
                        for l in range(window_height):
                            for m in range(window_width):
                                net.connect(ss_plane
                                    [j * (window_height - window_vert_overlap) + l]
                                    [k * (window_width - window_horiz_overlap) + m],
                                    model[current_layer + 2][i][j][k], shared_conv_weights[l][m])

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

