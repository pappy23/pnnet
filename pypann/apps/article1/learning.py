#!/usr/bin/env python

import math
import random
from pypann import *

if __name__ == "__main__":
    #Constructing perceptron
    net = multilayer_perceptron([1, 9, 4, 1], [TF.Linear, TF.Tanh, TF.Tanh, TF.Linear])

    #Learning
    train_data = generate_train_data(math.sin, -3.0, +3.0, 20)
    net.weight_randomization_attributes = Attributes()
    net.weight_randomization_attributes.min = -0.6
    net.weight_randomization_attributes.max = +0.6
    net.run(Runners.randomize_weights_according_to_inputs_count)
    lms(net, []) #dry run
    net.lms_attributes.learning_rate = 0.3
    net.lms_attributes.learning_momentum = 0.5

    epochs = 100
    train_error_info = []
    for i in range(1, epochs + 1):
        random.shuffle(train_data)
        train_error_info.append(mse(lms(net, train_data)))

    #Test run
    x = []
    f_x = []
    y = []
    err = []
    min_x = -4.0
    max_x = +4.0
    step_x = 0.01
    cur_x = min_x
    for i in range(int(round((max_x - min_x) / step_x))):
        net.set_input([cur_x])
        net.run()
        x.append(cur_x)
        f_x.append(math.sin(cur_x))
        y.append(net.get_output()[0])
        err.append(math.sin(cur_x) - net.get_output()[0])
        cur_x += step_x

    try:
        import matplotlib.pyplot as plt

        #Plot error graph
        plt.figure(1)
        plt.plot(range(1, epochs+1), train_error_info)
        plt.xlabel("epoch")
        plt.ylabel("error")

        #Plot test run graph
        plt.figure(2)
        ax = plt.subplot(1,1,1)
        ax.plot(x, f_x, color='g', label="f(x) = sin(x)")
        ax.plot(x, y, color='b', label="output")
        ax.plot(x, err, color='r', label="error")
        ax.grid(True)
        ax.axis([min_x, max_x, -1.5, +2])
        handles, labels = ax.get_legend_handles_labels()
        ax.legend(handles[::-1], labels[::-1])
        plt.show()
    except ImportError:
        print "Can't import matplotlib. Install it to get beautiful graphs"

