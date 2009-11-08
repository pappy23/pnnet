#
# ConvolutionalNetwork
#

from ..Core import *

def ConvolutionalNetwork(
        layers,
        connection_density,
        windows_height,
        window_width,
        window_horiz_overlap,
        window_vert_overlap,
        input_tf,
        conv_tf,
        ss_tf,
        output_tf):

    model = ConvolutionalNetworkModel(
        layers,
        connection_density,
        windows_height,
        window_width,
        window_horiz_overlap,
        window_vert_overlap,
        input_tf,
        conv_tf,
        ss_tf,
        output_tf
        )

    net = Net()

    for row in model[0][0]:
        for neuron in model[0][0][i]:
            net.add_input_neuron(neuron)

    return net

