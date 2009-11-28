#!/usr/bin/env python

#
# pann3d
#

import sys
import math
from pypann import *

def usage():
    return "Usage: pann3d <filename>"

def calc_coords(net):
    total_layers = len(net._cache.layers)
    for layer_no in range(total_layers):
        layer_size = len(net._cache.layers[layer_no])
        for i in range(layer_size):
            n = net._cache.layers[layer_no][i]
            plane_rows = math.sqrt(layer_size)
            plane_cols = layer_size // plane_rows
            if not hasattr(n, "opengl_attributes"):
                n.opengl_attributes = Attributes()
            if not hasattr(n.opengl_attributes, "x"):
                n.opengl_attributes.x = (layer - total_layers / 2.0 + 1) * 100.0
            if not hasattr(n.opengl_attributes, "y"):
                n.opengl_attributes.y = (i // plane_cols  - plane_rows / 2.0 + 1) * 40.0
            if not hasattr(n.opengl_attributes, "z"):
                n.opengl_attributes.z = (i %  plane_cols  - plane_cols / 2.0 + 1) * 40.0
            if not hasattr(n.opengl_attributes, "r"):
                n.opengl_attributes.r = 255.0
            if not hasattr(n.opengl_attributes, "g"):
                n.opengl_attributes.g = 0.0
            if not hasattr(n.opengl_attributes, "b"):
                n.opengl_attributes.b = 0.0

def draw(net):
    save(net, sys.argv[1])

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print usage()
        sys.exit(-1)

    net = load(sys.argv[1])
    # Debug
    for layer in net._cache.layers:
        print len(layer)

    draw(net)

