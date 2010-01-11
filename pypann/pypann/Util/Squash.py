#
# Squash
#

from ..Core import LogicError

def squash(data, src_min, src_max, dst_min, dst_max):
    """Scale list of values to new range

    To squah range [src_min; src_max] to new range [dst_min; dst_max] we use this formula:
    N = ( ( dst_max - dst_min ) / ( src_max - src_min ) ) * N +
    + ( dst_max - ( ( dst_max - dst_min ) / ( src_max - src_min ) ) * src_max )

    Signature: f(list[float], float, float, float, float) -> list[float]"""
    if src_min > src_max:
        src_min,src_max = src_max,src_min
    if dst_min > dst_max:
        dst_min,dst_max = dst_max,dst_min
    if src_min > min(data) or src_max < max(data):
        raise LogicError("Incorrect source range")
    # This check eliminates division by zero in some strange conditions
    if src_min == src_max:
        return [src_min] * len(data)
    a = float( dst_max - dst_min ) / float( src_max - src_min );
    b = dst_max - a * src_max;
    return map(lambda x: a * x + b, data)

