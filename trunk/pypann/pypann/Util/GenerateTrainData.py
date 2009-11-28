#
# GenerateTrainData
#

import random

def generate_train_data(f, min, max, count):
    """Generate list of train patterns for 1-to-1 network

    Result contains pairs (x, f(x)), where f is argument to function
    and x is sampled from [min; max] interval `count` times

    Signature: f(func, float, float, int) -> list[tuple[list[float], list[float]]]"""

    assert callable(f)
    assert isinstance(min, float)
    assert isinstance(max, float)
    assert isinstance(count, int)

    data = []
    for i in range(count):
        x = random.uniform(min, max)
        data.append( ([x], [f(x)]) )
    return data

