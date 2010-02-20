#
# Linear
#

from ..Core.TF import TF

class _Linear(TF):
    def f(self, x):
        return x

    def df(self, y):
        return 1

Linear = _Linear()

