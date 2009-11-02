#
# NetCache
#
class NetCache:
    def __init__(self):
        self._ok = False
        self.layers = []

    def is_ok(self):
        return self._ok

    def invalidate(self):
        self._ok = False

    def fix(self):
        self._ok = True

#
# Net
#
import multiprocessing
from Link import Link
from Queue import Queue
from threading import Thread

class Net:
    def __init__(self):
        self.input_neurons = []
        self.worker_threads_count = multiprocessing.cpu_count()
        self._cache = NetCache()

    def add_input_neuron(self, n):
        self.input_neurons.append(n)
        self._cache.invalidate()

    def remove_neuron(self, n):
        for link in n._links_in:  self.disconnect(link.to(), n)
        for link in n._links_out: self.disconnect(n, link.to())

        try:
            self.input_neurons.remove(n)
        except ValueError:
            pass

        del n

        self._cache.invalidate()

    def connect(self, n_from, n_to, w, latency = 1):
        n_from._links_out.append(Link(n_to, w, latency))
        n_to._links_in.append(Link(n_from, w, latency))
        self._cache.invalidate()

    def disconnect(self, n_from, n_to):
        n_from._links_out = [link for link in n_from._links_out if link.to() != n_to]
        n_to._links_in = [link for link in n_to._links_in if link.to() != n_from]
        self._cache.invalidate()

    def set_input(self, values):
        for i in range(len(self.input_neurons)):
            self.input_neurons[i].input = values[i]

    def get_output(self):
        if not self._cache.is_ok():
            self._update_cache()

        if len(self._cache.layers):
            return map(lambda n: n.output, self._cache.layers[-1])
        else:
            return []

    #dir - True - forward run, False - backward
    def run(self, runner, dir = True):
        if not self._cache.is_ok():
            self._update_cache()

        def worker():
            while True:
                neuron = q.get()
                runner(neuron)
                q.task_done()

        q = Queue()
        for i in range(self.worker_threads_count):
            t = Thread(target=worker)
            t.setDaemon(True)
            t.start()

        for l in self._cache.layers:
            for n in l:
                q.put(n)
            q.join()


        pass #TODO join all

    def _update_cache(self):
        self._cache.layers = []
        hops = dict(map(lambda x: (x, 1), self.input_neurons))

        layer = set(self.input_neurons)
        while len(layer):
            self._cache.layers.append(layer)
            next_layer = set()
            for n in layer:
                for link in n._links_out:
                    if not link.to() in hops:
                        hops[link.to()] = hops[n] + link.latency()
                    if hops[link.to()] == hops[n] + 1:
                        next_layer.add(link.to())
                layer = next_layer

        self._cache.fix()

#
# Testing
#
from Weight import Weight
from Neuron import *

def test_Net():
    print "Testing Net..."

    N = Net()
    print N.get_output()

    n = {}
    for i in range(4):
        n[i] = Neuron()

    def runner(N):
        pass

    def print_cache(N):
        print "Cache:"
        N.run(runner)
        for l in N._cache.layers:
            print [x for x in range(len(n)) for neu in l if n[x] == neu]

    N.add_input_neuron(n[0])
    N.connect(n[0], n[1], Weight(3.0))
    N.connect(n[0], n[2], Weight())
    N.connect(n[1], n[3], Weight())
    N.connect(n[2], n[3], Weight())
    print_cache(N)
    print N.get_output()

    N.remove_neuron(n[3])
    print_cache(N)

#
# Main
#
if __name__ == "__main__":
    test_Net()

