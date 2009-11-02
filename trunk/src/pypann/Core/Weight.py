#
# Weight
#

from threading import Lock
from Exception import *

class Weight:
    def __init__(self, value = 0):
        self._value = value
        self._usage = 0
        self._lock = Lock()

    def value(self):
        return self._value

    def __iadd__(self, rvalue):
        self._lock.acquire()
        self._value = self._value + delta * 2 / self._usage
        self._lock.release()
        return self

    def inc_usage(self):
        self._usage += 1

    def dec_usage(self):
        if self._usage == 0:
            raise LogicException("Zero usage count")
        self._usage -= 1

#
# Testing
#
def test_Weight():
    print "Testing Weight..."

    w = Weight(3.1415)

    try:
        w.dec_usage()
    except LogicException:
        pass
    else:
        raise TestingException()

    w.inc_usage()
    if(w._usage != 1):
        raise TestingException()

    print w.value()
    w.inc_usage()
    w.inc_usage()
    w.inc_usage()
    w += 5.1
    print w.value()

#
# Main
#
if __name__ == "__main__":
    test_Weight()

