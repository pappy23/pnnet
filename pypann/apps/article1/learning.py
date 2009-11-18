
import math
import random
import matplotlib.pyplot as plt
from pypann import *

def gen_data(min, max, count, f):
    data = []
    for i in range(count):
        x = random.uniform(min, max)
        data.append( ([x], [f(x)]) )
    return data

def mse(data):
    if isinstance(data[0], float): #Train pattern
        return reduce(lambda x, y: x + y, map(lambda x: x * x, data)) / 2.0
    elif isinstance(data[0], list):
        acc = 0
        for pattern in data:
            acc += mse(pattern)
        return acc / len(data)
    else:
        raise LogicError("Wrong input type")

if __name__ == "__main__":
    #Constructing perceptron
    net = multilayer_perceptron([1, 9, 4, 1], [TF.Linear, TF.Tanh, TF.Tanh, TF.Linear])

    #Learning
    train_data = gen_data(-3.0, +3.0, 20, math.sin)
    net.weight_randomization_attributes = Attributes()
    net.weight_randomization_attributes.min = -0.6
    net.weight_randomization_attributes.max = +0.6
    net.run(Runners.randomize_weights_according_to_inputs_count)
    Lms.init(net)
    net.lms_attributes.learning_rate = 0.3
    net.lms_attributes.learning_momentum = 0.5

    epochs = 100
    train_error_info = []
    for i in range(1, epochs + 1):
        random.shuffle(train_data)
        train_error_info.append(mse(lms(net, train_data)))

    #Plot error graph
    plt.figure(1)
    plt.plot(range(1, epochs+1), train_error_info)
    plt.xlabel("epoch")
    plt.ylabel("error")

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

