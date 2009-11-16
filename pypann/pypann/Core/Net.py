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
from multiprocessing import cpu_count
from Queue import Queue
from threading import Thread, Lock
from Link import Link
from Weight import Weight

class Net:
    def __init__(self):
        self.input_neurons = []
        self.worker_threads_count = cpu_count()
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

    def connect(self, n_from, n_to, w = None, latency = 1):
        if w == None:
            w = Weight()
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

    def run(self, runner = lambda x, y: x.run(), dir = True):
        """
        Use runner on all neurons

        runner := func(neuron, net)
        dir := True | False
        if dir == True then perform feedforward run, else - backward run
        """
        def worker():
            while True:
                runner(queue.get(False), self)
                queue.task_done()
                if not job_is_done.locked():
                    break

        if not self._cache.is_ok():
            self._update_cache()

        if not dir:
            self._cache.layers.reverse()

        queue = Queue()
        threads = []
        job_is_done = Lock()
        with job_is_done:
            for i in range(self.worker_threads_count):
                t = Thread(target=worker)
                t.daemon = True
                t.start()
                threads.append(t)

            for layer in self._cache.layers:
                for neuron in layer:
                    queue.put(neuron)
                queue.join()

        if not dir:
            self._cache.layers.reverse()

        #for t in threads:
        #    t.join(1)
        #FIXME: This hangs all the time

    def _update_cache(self):
        """
        Rebuild internal cache on demand
        """
        self._cache.layers = []
        hops = dict(map(lambda x: (x, 1), self.input_neurons))

        layer = set(self.input_neurons)
        while len(layer):
            self._cache.layers.append(list(layer))
            next_layer = set()
            for n in layer:
                for link in n._links_out:
                    if not link.to() in hops:
                        hops[link.to()] = hops[n] + link.latency()
                    if hops[link.to()] == hops[n] + 1:
                        next_layer.add(link.to())
                layer = next_layer

        self._cache.fix()
