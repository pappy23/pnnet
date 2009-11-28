#
# RandomizeWeightsAccordingToInputsCount
#

import random
import math
from ..Core import Attributes

default_min = -2.4
default_max = +2.4

def randomize_weights_according_to_inputs_count(neuron, net):
    if not hasattr(net, "weight_randomization_attributes"):
        net.weight_randomization_attributes = Attributes()
        net.weight_randomization_attributes.min = default_min
        net.weight_randomization_attributes.max = default_max

    C = math.sqrt(len(neuron._links_in))

    for l in neuron._links_in:
        l.weight()._value = random.uniform(net.weight_randomization_attributes.min, net.weight_randomization_attributes.max) / C

