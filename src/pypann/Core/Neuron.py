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

    def run():
        pass

#af - раз нейрон содержит Runner, то пусть он и занимается всякими ф-ями авктивации. Пусть хранит ее в нейроне как аттрибут
#bias - Сделать Link, который меняет поведение. Может содержать Weight, а может просто ф-ю. Bias можно реализовать через ф-ю Link-а

"""
Testing
"""
def test_Neuron():
    print "Testing Neuron..."


if __name__ == "__main__":
    test_Neuron()
