#
# Teacher
#

from ..Core import Net
from ..Runners import feedforward_propagation

def teach(net, data, runner):
    """
    Implements learning with teacher

    data := list(pattern, ...)
    pattern := tuple(input, desired_output)
    input, desired_output := list(value, ...)
    """
    assert(isinstance(net, Net))
    assert(isinstance(data, list))
    assert(hasattr(runner, "__call__"))

    error = []
    for pattern in data:
        net.set_input(pattern[0])
        net.run(feedforward_propagation)
        actual_output = net.get_output()
        pattern_error = []
        for i in range(len(net._cache.layers[-1])): #TODO: check for null length
            net._cache.layers[-1][i].error = pattern[1][i] - actual_output[i]
            pattern_error.append(net._cache.layers[-1][i].error)
        error.append(pattern_error)
        net.run(runner, False)
    return error
