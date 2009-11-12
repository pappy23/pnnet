#
# Teacher
#

from ..Core import Net
from ..Runners import feedforward_propagation

def teach(net, data, runner):
    """
    pattern = (input, desired_output)
    """
    assert(isinstance(net, Net))
    assert(isinstance(data, list))
    assert(hasattr(runner, "__call__"))
      
    for pattern in data:
        net.set_input(pattern[0]) 
        net.run(feedforward_propagation)
        actual_output = net.get_output()
        for i in range(len(net._cache.layers[-1])):
            net._cache.layers[-1][i].error = pattern[1][i] - actual_output[i]
        net.run(runner, False)
