#
# RandomizeWeightsGauss
#

import random
import math
from ..Core.Attributes import Attributes

default_min = -0.3
default_max = +0.3

def randomize_weights_gauss(neuron, net):
    if not hasattr(net, "weight_randomization_attributes"):
        net.weight_randomization_attributes = Attributes()
        net.weight_randomization_attributes.min = default_min
        net.weight_randomization_attributes.max = default_max

    for l in neuron._links_in:
        l.weight()._value = random.uniform(net.weight_randomization_attributes.min, net.weight_randomization_attributes.max)

