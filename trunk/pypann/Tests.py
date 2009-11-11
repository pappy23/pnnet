#
# Tests
#

import unittest
from pypann import *

class ExceptionTestCase(unittest.TestCase):
    def _helper(self):
        raise LogicError("Test error occured")

    def runTest(self):
        self.assertRaises(LogicError, self._helper)

class MooTestCase(unittest.TestCase):
    def runTest(self):
        for i in range(7):
            pass #moo()

class TFTestCase(unittest.TestCase):
    def testTanh(self):
        self.assertAlmostEqual(TF.Tanh.f(5.0), 1.71, 2)
        self.assertAlmostEqual(TF.Tanh.f(-5.0), -1.71, 2)
        self.assertAlmostEqual(TF.Tanh.df(-1.0), 0.76, 2)

    def testThreshold(self):
        self.assertEqual(TF.Threshold.f(5.0), 1.0)
        self.assertEqual(TF.Threshold.f(0.0), 1.0)
        self.assertEqual(TF.Threshold.f(-5.0), 0)
        self.assertEqual(TF.Threshold.df(0.0), float('inf'))
        self.assertEqual(TF.Threshold.df(4.0), 0)

    def testLinear(self):
        self.assertEqual(TF.Linear.f(5.0), 5.0)
        self.assertEqual(TF.Linear.df(-4.0), 1)

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
        self.assertEqual(self.link.to(), None)
        self.assertEqual(self.link.weight()._usage, 1)
        self.assertEqual(self.link.latency(), 2)

class NeuronTestCase(unittest.TestCase):
    def runTest(self):
        self.neuron = Neuron()
        self.assertEqual(self.neuron.input, 0)
        self.assertEqual(self.neuron.output, 0)

class PyramidalNeuronTestCase(unittest.TestCase):
    def testRun(self):
        class Linear:
            def f(self, x):
                return x

        n = PyramidalNeuron(Linear())
        n.input = 5
        n.run()
        self.assertEqual(n.output, 5.0)

class BiasNeuronTestCase(unittest.TestCase):
    def runTest(self):
        net = Net()
        n1 = PyramidalNeuron(TF.Tanh)
        net.add_input_neuron(n1)
        net.connect(BiasNeuron(), n1, Weight(1.0))
        net.run()
        self.assertEqual(net.get_output(), [TF.Tanh.f(1.0)])

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
        net._update_cache()
        self.assertEqual(len(net._cache.layers), 3)
        #self.print_cache(net)
        net.remove_neuron(net._cache.layers[-1][0])
        net._update_cache()
        self.assertEqual(len(net._cache.layers), 2)
        #self.print_cache(net)

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

class WeightRandomizationTestCase(unittest.TestCase):
    def setUp(self):
        self.net = Net()
        n1 = Neuron()
        n2 = Neuron()
        self.net.add_input_neuron(n1)
        self.net.connect(n1, n2)
        self.net.connect(BiasNeuron(), n2)

    def printWeights(self):
        self.net.run()
        for layer in self.net._cache.layers:
            for neuron in layer:
                for link in neuron._links_in:
                    print "N(", neuron, "):\t", link.weight().value()

    def testRandomizeWeightsGauss(self):
        #print "RandomizeWeightsGauss"
        self.net.run(Runners.randomize_weights_gauss)
        #self.printWeights()

    def testRandomizeWeightsAccordintToInputsCount(self):
        #print "RandomizeWeightsAccordintToInputsCount"
        self.net.run(Runners.randomize_weights_according_to_inputs_count)
        #self.printWeights()

class MultilayerPerceptronTestCase(unittest.TestCase):
    def runTest(self):
        net = multilayer_perceptron([3, 2, 1], [TF.Linear, TF.Linear, TF.Linear])
        net.run()
        self.assertEqual(net.get_output()[0], 3.0)

class ConvolutinalNetworkTestCase(unittest.TestCase):
    def runTest(self):
        net = convolutional_network([1,1,1])
        pass #TODO

class FeedforwardPropagationRunnerTestCase(unittest.TestCase):
    def runTest(self):
        net = Net()
        n1 = PyramidalNeuron(TF.Linear())
        n2 = PyramidalNeuron(TF.Linear())
        net.add_input_neuron(n1)
        net.connect(n1, n2, Weight(1.0))
        net.connect(BiasNeuron(), n2, Weight(1.0))
        net.set_input([1.0])
        net.run(Runners.feedforward_propagation)
        self.assertEqual(net.get_output(), [2.0])

class LmsTestCase(unittest.TestCase):
    def runTest(self):
        net = Net()
        n1 = PyramidalNeuron(TF.Linear())
        n2 = PyramidalNeuron(TF.Linear())
        net.add_input_neuron(n1)
        net.connect(n1, n2, Weight(1.0))
        net.connect(BiasNeuron(), n2, Weight(1.0))
        n2.lms_attributes = Attributes()
        n2.lms_attributes.error = 5.0
        net.lms_attributes = Attributes()
        net.lms_attributes.learning_rate = 0.1
        net.lms_attributes.learning_momentum = 0.5
        net.lms_attributes.epoch = 1
        net.lms_attributes.annealing_tsc = 10
        net.run(Runners.lms_runner, False)
        #TODO Train net in loop

#
# Main
#
if __name__ == "__main__":
    print unittest.main()
