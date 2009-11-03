"""
Runner
"""

class Runner:
    def run(self, obj):
        pass

class NeuronRunner(Runner):
    def _run_af(self, neuron):
        pass

    def run(self, neuron):
        if hasattr(neuron, "_af"):
            self._run_af(neuron)
        pass

class LinkRunner(Runner):
    def run(self, link):
        pass

if __name__ == "__main__":
    pass

