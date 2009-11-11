#
# Teacher
#

def teach(net, data, runner):
    assert(isinstance(net, Net))
    assert(isinstance(data, list))
    assert(isinstance(runner, function))

    output_neurons = net._cache.layers[-1]
    for pattern in data:
        net.set_input(pattern[0])
        net.run(runner, False)
        output = net.get_output()
        #TODO
    pass

