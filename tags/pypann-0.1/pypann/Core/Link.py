#
# Link
#

from Weight import Weight

class Link:
    """Link to neuron"""

    def __init__(self, to, weight, latency):
        self._to = to
        self._weight = weight
        self._latency = latency

        if isinstance(weight, Weight):
            self._weight.inc_usage()

    def to(self):
        """Returns neuron to which this link is connected"""
        return self._to

    def weight(self):
        """Returns reference to shared Weight object"""
        return self._weight

    def latency(self):
        """Returns latency of link"""
        return self._latency

