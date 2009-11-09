#
# MultilayerPerceptron
#

from ..Core.Weight import Weight
from ..Core.Net import Net
from ..Neurons.PyramidalNeuron import PyramidalNeuron
from ..Neurons.BiasNeuron import BiasNeuron
from ..TF import Linear, Tanh

def multilayer_perceptron(layers, tfs = []):
    net = Net()

    if len(layers) == 0:
        return net

    mlp = []
    for i in range(len(layers)):
        if i > len(tfs) - 1:
            if i == len(layers) - 1:
                tf = Linear()
            else:
                tf = Tanh()
        else:
            tf = tfs[i]

        mlp.append([])
        for j in range(layers[i]):
            n = PyramidalNeuron(tf)
            mlp[i].append(n)
            if i == 0:
                net.add_input_neuron(n)
            else:
                net.connect(BiasNeuron(), n, Weight(1.0))

    for i in range(len(mlp) - 1):
        for j in range(len(mlp[i])):
            for k in range(len(mlp[i+1])):
                net.connect(mlp[i][j], mlp[i+1][k], Weight(1.0))

    return net

