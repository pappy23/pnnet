#
# Link
#

from Weight import Weight

class Link:
    def __init__(self, to, weight, latency):
        self._to = to
        self._weight = weight
        self._latency = latency

        if isinstance(weight, Weight):
            self._weight.inc_usage()

    def to(self):
        return self._to

    def weight(self):
        return self._weight

    def latency(self):
        return self._latency

#
# Testing
#

import unittest

class LinkTestCase(unittest.TestCase):
    def runTest(self):
        self.link = Link(None, Weight(3.0), 2)
        self.assertEqual(self.link.weight()._usage, 1)
        print self.link.to(), self.link.weight(), self.link.latency()

#
# Main
#
if __name__ == "__main__":
    unittest.main()

