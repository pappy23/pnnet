#
# Weight
#

from threading import Lock
from Exception import LogicError

class Weight:
    def __init__(self, value = 0):
        self._value = value
        self._usage = 0
        self._lock = Lock()

    def value(self):
        return self._value

    def add_value(self, value):
        with self._lock:
            self._value = self._value + value * 2 / self._usage

    def __iadd__(self, rvalue):
        self.add_value(rvalue)
        return self

    def inc_usage(self):
        self._usage += 1

    def dec_usage(self):
        if self._usage == 0:
            raise LogicError("Zero usage count")
        self._usage -= 1

    def __getstate__(self):
        odict = self.__dict__.copy()
        del odict["_lock"]
        return odict

    def __setstate__(self, dict):
        self.__dict__.update(dict)
        self._lock = Lock()

