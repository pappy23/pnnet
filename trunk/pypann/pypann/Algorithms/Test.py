#
# Test
#

from ..Core import Net
from ..Runners import feedforward_propagation
from ..Util import mse

def test(net, data):
    """Runs network with data and calculates execution error

    Signature: f(Net, list[tuple[list[float], list[float]]]) -> list[float]"""
    assert isinstance(net, Net)
    assert isinstance(data, list)

    errors = []
    for p in data:
        net.set_input(p[0])
        net.run(feedforward_propagation, True)
        actual_output = net.get_output()
        e = map(lambda x, y: x - y, p[1], actual_output)
        errors.append(mse(e))
    return errors

