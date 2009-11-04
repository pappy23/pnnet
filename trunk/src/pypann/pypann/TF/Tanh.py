#
# Tanh
#

from ..Core.TF import TF

class _Tanh(TF):
    def f(self, x):
        pass #TODO

    def df(self, x):
        return 1

Tanh = _Tanh()

