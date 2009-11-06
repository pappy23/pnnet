
# PyramidalNeuron
#

from ..Core.Neuron import Neuron

class PyramidalNeuron(Neuron):
    def __init__(self, tf):
        #super(self.__class__, self).__init__() #FIXME
        Neuron.__init__(self)
        self.tf = tf

    def run(self):
        if self.tf:
            for link in self._links_in:
                self.input += link.to().output * link.weight().value()
            self.output = self.tf.f(self.input)
        self.input = 0

