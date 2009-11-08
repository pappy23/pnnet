#
# Storage
#

import cPickle

def load(filename):
    file = open(filename, "rb")
    with file:
        return cPickle.load(file)

def save(obj, filename):
    file = open(filename, "wb")
    with file:
        cPickle.dump(obj, file)

