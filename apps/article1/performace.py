#!/usr/bin/env python

from pypann import *
from timeit import Timer
import time, random

if __name__ == "__main__":
    #Constructing perceptron
    net = multilayer_perceptron([1, 1000, 1], [TF.Linear, TF.Tanh, TF.Tanh, TF.Tanh, TF.Linear])

    #Dry run to create all internal structures
    net.worker_threads_count = 1
    net.run(Runners.randomize_weights_according_to_inputs_count)
    lms(net, [([1], [1])])

    def delay_runner(neuron, net):
        for i in range(500000):
            a = random.random()

    #t = Timer("lms(net, [([1], [1])])", "from __main__ import net, lms")
    t = Timer("net.run(delay_runner)", "from __main__ import net, time, delay_runner")
    for i in range(5, 6):
        print "Threads:", i
        net.worker_threads_count = i
        print "%.2f usec" % (1000000 * t.timeit(number=1))

