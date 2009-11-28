#!/usr/bin/env python

from pypann import *
from timeit import Timer
import time

if __name__ == "__main__":
    #Constructing perceptron
    net = multilayer_perceptron([1, 200, 200, 200, 1], [TF.Linear, TF.Tanh, TF.Tanh, TF.Tanh, TF.Linear])

    #Dry run to create all internal structures
    net.run(Runners.randomize_weights_according_to_inputs_count)
    lms(net, [([1], [1])])

    #t = Timer("lms(net, [([1], [1])])", "from __main__ import net, lms")
    t = Timer("net.run(lambda x,y: time.sleep(0.01))", "from __main__ import net, time")
    for i in range(1, 9):
        print "Threads:", i
        net.worker_threads_count = i
        print "%.2f usec" % (1000000 * t.timeit(number=10))

