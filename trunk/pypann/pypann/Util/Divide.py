#
# Divide
#

from numpy import *

def divide(data, percentage):
    """Percentagewise divide numpy array into two

    Signature: f(array[*]) -> tuple[list[*], list[*]]"""
    assert isinstance(data, ndarray)
    assert isinstance(percentage, int)
    assert 0 < percentage < 100

    count = len(data) * percentage // 100
    return (data[:count], data[count:])

