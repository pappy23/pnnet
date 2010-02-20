#
# Threshold
#

from ..Core.TF import TF

class _Threshold(TF):
    def f(self, x):
        if x < 0:
            return 0
        return 1

    def df(self, y):
        if y == 0:
            return float('inf')
        return 0

Threshold = _Threshold()

