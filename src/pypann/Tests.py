#
# Tests
#

import unittest
from pypann import *

class ExceptionTestCase(unittest.TestCase):
    def runTest(self):
        try:
            raise LogicError("Test error occured")
        except LogicError as e:
            print e

class MooTestCase(unittest.TestCase):
    def runTest(self):
        for i in range(7):
            pass #moo()

class WeightTestCase(unittest.TestCase):
    def setUp(self):
        self.weight = Weight(3.1415)

    def testUsage(self):
        self.weight._usage = 0
        self.assertRaises(LogicError, self.weight.dec_usage)
        self.weight.inc_usage()
        self.assertEqual(self.weight._usage, 1)

    def testAdd(self):
        self.weight._usage = 4
        self.weight += 5.1
        self.assertAlmostEqual(self.weight.value(), 5.69, 2)

class LinkTestCase(unittest.TestCase):
    def runTest(self):
        self.link = Link(None, Weight(3.0), 2)
        self.assertEqual(self.link.weight()._usage, 1)
        print self.link.to(), self.link.weight(), self.link.latency()

class NeuronTestCase(unittest.TestCase):
    def setUp(self):
        self.neuron = Neuron()

    def runTest(self):
        print "Input: %s" % self.neuron.input
        print "Output: %s" % self.neuron.output

class PyramidalNeuronTestCase(unittest.TestCase):
    def testRun(self):
        class Linear:
            def f(self, x):
                return x

        n = PyramidalNeuron(Linear())
        n.input = 5
        n.run()
        self.assertEqual(n.output, 5.0)

class NetTestCase(unittest.TestCase):
    class LinearTF:
        def f(self, x):
            return x

    def compose_typical_net(self):
        net = Net()
        n = {}
        for i in range(4):
            n[i] = PyramidalNeuron(TF.Linear)
            n[i].tag = i
        net.add_input_neuron(n[0])
        net.connect(n[0], n[1], Weight(3.0))
        net.connect(n[0], n[2], Weight(3.0))
        net.connect(n[1], n[3], Weight(0.5))
        net.connect(n[2], n[3], Weight(0.5))
        return net

    def print_cache(self, net):
        print "Cache:"
        if not net._cache.is_ok():
            net._update_cache()

        for l in net._cache.layers:
            print [x.tag for x in l]

    def testCache(self):
        net = self.compose_typical_net()
        self.print_cache(net)
        net.remove_neuron(net._cache.layers[-1][0])
        self.print_cache(net)

    def testRun(self):
        net = self.compose_typical_net()
        net._update_cache()
        net.set_input([5.0])
        net.run()
        self.assertEqual(net.get_output(), [15.0])

    def testStorage(self):
        net = self.compose_typical_net()
        net._update_cache()
        c1 = net._cache.layers
        save(net, "test.net")
        net2 = load("test.net")
        for i in range(len(c1)):
            for j in range(len(c1[i])):
                self.assertEqual(c1[i][j].tag, net2._cache.layers[i][j].tag)


#
# Main
#
if __name__ == "__main__":
    print unittest.main()

