#
# Lms
#

from ..Core import Net
from ..Runners import init_net, lms_runner
from Teacher import teach

def lms(net, data):
    """
    Least Mean Squared algorithm

    Implements LMS(gradient descent) algorithm
    Returns list of errors for all epochs

    Signature: f(Net, list[tuple[list[float], list[float]]]) -> list[float]"""

    assert isinstance(net, Net)
    assert isinstance(data, list)

    if not hasattr(net, "lms_attributes"):
        init_net(net)

    attrs = net.lms_attributes

    #===========================================================================
    # Simulated annealing, rate = basic_rate / ( 1 + epoch / time_seek_constant)
    # When epoch -> inf, rate -> basic_rate / epoch
    #===========================================================================
    attrs.actual_learning_rate = attrs.learning_rate / (1 + (attrs.epoch / attrs.annealing_tsc));

    error = teach(net, data, lms_runner)
    attrs.epoch += 1
    return error

