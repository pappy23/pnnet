"""
Link
"""

from Weight import Weight

class Link:
    def __init__(self, to, w, latency):
        self._to = to
        self._w = w
        self._latency = latency

        if isinstance(w, Weight):
            w.inc_usage()

    def get_to(self):
        return self._to

    def get_w(self):
        return self._w

    def get_latency(self):
        return self._latency

"""
Testing
"""
def test_Link():
    print "Testing Link..."
    l = Link(None, Weight(), 1)
    print l.get_to(), l.get_w(), l.get_latency()

if __name__ == "__main__":
    test_Link()

