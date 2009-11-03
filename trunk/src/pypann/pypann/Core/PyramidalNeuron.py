#
# PyramidalNeuron
#

from Neuron import Neuron

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

#
# Testing
#

import unittest
from Weight import Weight
from Link import Link

class PyramidalNeuronTestCase(unittest.TestCase):
    def testRun(self):
        class Linear:
            def f(self, x):
                return x

        n = PyramidalNeuron(Linear())
        n.input = 5
        n.run()
        assertEqual(n.output, 5.0)

#
# Main
#
if __name__ == "__main__":
    unittest.main()

