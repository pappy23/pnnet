#
# Weight
#

import threading
import Exception

class Weight:
    def __init__(self, value = 0):
        self._value = value
        self._usage = 0
        self._lock = threading.Lock()

    def value(self):
        return self._value

    def __iadd__(self, rvalue):
        with self._lock:
            self._value = self._value + rvalue * 2 / self._usage
        return self

    def inc_usage(self):
        self._usage += 1

    def dec_usage(self):
        if self._usage == 0:
            raise Exception.LogicException("Zero usage count")
        self._usage -= 1

#
# Testing
#

import unittest

class WeightTestCase(unittest.TestCase):
    def setUp(self):
        self.weight = Weight(3.1415)

    def testUsage(self):
        self.weight._usage = 0
        self.assertRaises(Exception.LogicException, self.weight.dec_usage)
        self.weight.inc_usage()
        self.assertEqual(self.weight._usage, 1)

    def testAdd(self):
        self.weight._usage = 4
        self.weight += 5.1
        self.assertAlmostEqual(self.weight.value(), 5.69, 2)

#
# Main
#
if __name__ == "__main__":
    unittest.main()

