#
# BiasNeuron
#

from ..Core import Neuron

#FIXME: We are wasting memory with current implementation of bias neuron mechanism
class BiasNeuron(Neuron): # needed to pass type chacks in Net
    def __init__(self):
        Neuron.__init__(self)
        #self._links_out = []
        self.output = 1.0

