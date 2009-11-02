#
# Neuron
#

from Weight import Weight
from Link import Link

class Neuron:
    def __init__(self):
        self._links_in = []
        self._links_out = []
        self.input = 0
        self.output = 0

    def run(self):
        pass

class PyramidalNeuron(Neuron):
    def __init__(self, tf):
        #super(self.__class__, self).__init__()
        Neuron.__init__(self)
        self.tf = tf

    def run(self):
        if self.tf:
            for link in self._links_in:
                self.input += link.get_to().output * link.get_weight().get_value()
            self.output = self.tf.f(self.input)
        self.input = 0

#
# Testing
#
def test_Neuron():
    print "Testing Neuron..."
    class Linear:
        def f(self, x):
            return x
    
    n = PyramidalNeuron(Linear())
    n.input = 5
    n.run()
    print n.output

#
# Main
#
if __name__ == "__main__":
    test_Neuron()

