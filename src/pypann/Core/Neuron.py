#
# Neuron
#

class Neuron:
    def __init__(self):
        self._links_in = []
        self._links_out = []
        self.input = 0
        self.output = 0

    def run(self):
        pass

#
# Testing
#

import unittest

class NeuronTestCase(unittest.TestCase):
    def setUp(self):
        self.neuron = Neuron()

    def runTest(self):
        print "Input: %s" % self.neuron.input
        print "Output: %s" % self.neuron.output

#
# Main
#
if __name__ == "__main__":
    unittest.main()

