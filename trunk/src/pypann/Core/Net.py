"""
Net
"""

class NetCache:
    def __init__(self):
        self._ok = False
        self.layers = []

    def is_ok(self):
        return _ok

    def invalidate(self):
        _ok = False

    def fix(self):
        _ok = True

from Link import Link

class Net:
    def __init__(self): #TODO
        self.input_neurons = []
        self.worker_threads_count = 2
        self._cache = NetCache()

    def add_input_neuron(self, n):
        self.input_neurons.append(n)
        self._cache.invalidate()

    def remove_neuron(self, n): #TODO
        for link in n._links_in:
            disconnect(link.get_to, n)
        for link in n._links_out:
            disconnect(n, link.get_to)

        try:
            self.input_neurons.remove(n)
        except ValueError:
            pass

        #delete(n) ???

        self._cache.invalidate()

    def connect(self, n_from, n_to, w, latency = 1):
        n_from._links_out.append(Link(n_to, w, latency))
        n_to._links_in.append(Link(n_from, w, latency))
        self._cache.invalidate()

    def disconnect(self, n_from, n_to): #TODO
        pass
        self._cache.invalidate()

    def set_input(self, values):
        for i in range(len(self.input_neurons)):
            self.input_neurons[i].input = values[i]

    def get_output(self): #TODO
        if not self._cache.is_ok():
            _update_cache()

        return []

    #dir - True - forward run, False - backward
    def run(self, dir = True): #TODO
        if not self._cahce.is_ok():
            _update_cache()

        for i in range(worker_threads_count):
            pass #TODO: spawn thread

        pass #TODO join all

    def _push_layer_to_cache(layer):
        pass #TODO

    def _update_cache(self): #TODO
        self._cache.layers = []
        raw_layer = []
        hops = {}

        for n in input_neurons:
            raw_layer.append(n)
            hops[n] = 1

        _push_layer_to_cache(raw_layer)

        self._cache.fix()

def test_Net():
    from Weight import Weight
    from Neuron import Neuron

    print "Testing Net..."

    N = Net()
    n1 = Neuron()
    n2 = Neuron()
    N.add_input_neuron(n1)
    N.connect(n1, n2, Weight(3.0))

if __name__ == "__main__":
    test_Net()

