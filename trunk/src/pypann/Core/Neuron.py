# -*- encoding: utf-8

"""
Neuron
"""

from Weight import Weight
from Link import Link

class Neuron:
    def __init__(self):
        self._links_in = []
        self._links_out = []
        self.input = 0
        self.output = 0

    def run(self):
        pass

class PyramidalNeuron:
    def __init__(self, tf):
        self.Neuron.__init__()
        self.tf = tf

    def run():
        for link in _links_in:
            if self.tf:
                self.input += link.get_to().output * link.get_weight().get_value()
                self.output = self.tf.f(self.input)

#af - раз нейрон содержит Runner, то пусть он и занимается всякими ф-ями авктивации. Пусть хранит ее в нейроне как аттрибут
#bias - Сделать Link, который меняет поведение. Может содержать Weight, а может просто ф-ю. Bias можно реализовать через ф-ю Link-а

"""
Testing
"""
def test_Neuron():
    print "Testing Neuron..."
    def pyramidal_runner(n):
        for l in n._links_in:
            


if __name__ == "__main__":
    test_Neuron()
