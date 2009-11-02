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
def test_Link():
    print "Testing Link..."
    l = Link(None, Weight(3.0), 1)
    print l.to(), l.weight(), l.latency()

#
# Main
#
if __name__ == "__main__":
    test_Link()

