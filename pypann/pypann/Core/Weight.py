#
# Weight
#

from threading import Lock
from Exception import LogicError

class Weight:
    """Link weight, might be shared by different links

    It holds float value and organizes concurrent access to it
    with internal threading::Lock object
    """

    def __init__(self, value = 0):
        self._value = value
        self._usage = 0
        self._lock = Lock()

    def value(self):
        """Returns stored value"""
        return self._value

    def add_value(self, value):
        """Adds supplied value to weight internal value. Thread safe."""
        assert type(value) is float or type(value) is int

        with self._lock:
            self._value = self._value + value * 2 / self._usage

    def __iadd__(self, rvalue):
        """See Weight.add_value"""
        self.add_value(rvalue)
        return self

    def inc_usage(self):
        """Incements internal usage counter"""
        self._usage += 1

    def dec_usage(self):
        """Decrements usage counter"""
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

