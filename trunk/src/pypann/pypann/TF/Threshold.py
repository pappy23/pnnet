#
# Threshold
#

from ..Core.TF import TF

class _Threshold(TF):
    def f(self, x):
        pass #TODO

    def df(self, x):
        return 1

Threshold = _Threshold()

