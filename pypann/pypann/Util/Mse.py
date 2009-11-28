#
# Mse
#

def mse(data):
    """Calculate mean squared error for a supplied data

    If data is a list of float values then return averaged sum of
    squared elements of a list
    If data is a list of lists - return averaged sum of mean squared
    errors of contained lists

    Signature: f(list[float]) -> float
               f(list[list[float]]) -> float"""
    if isinstance(data[0], float): #Train pattern
        return reduce(lambda x, y: x + y, map(lambda x: x * x, data)) / 2.0
    elif isinstance(data[0], list):
        acc = 0
        for pattern in data:
            acc += mse(pattern)
        return acc / len(data)
    else:
        raise LogicError("Wrong input type")

