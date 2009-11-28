#
# Divide
#

def divide(data, percentage):
    """Percentagewise divide list into two

    Signature: f(list[*]) -> tuple[list[*], list[*]]"""
    assert isinstance(data, list)
    assert isinstance(percentage, int)
    assert 0 < percentage < 100

    count = len(data) * percentage // 100
    first = []
    second = []
    for i in range(count):
        first.append(data[i])
    for i in range(count, len(data)):
        second.append(data[i])
    return (first, second)

