#
# Tanh
#

import math
from ..Core.TF import TF

class _Tanh(TF):
    def f(self, x):
        return self.a * math.tanh( self.b * x )

    def df(self, y):
        return self.b/self.a * (self.a - y) * (self.a + y)

Tanh = _Tanh()
Tanh.a = 1.7179
Tanh.b = 2.0 / 3.0

