#
# Neuron
#

class Neuron:
    """Base class for various types of neurons

    Holds input, output and two lists of links(to neuron and from neuron)
    """

    def __init__(self):
        self._links_in = []
        self._links_out = []
        self.input = 0
        self.output = 0

    def run(self):
        pass

