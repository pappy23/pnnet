#!/usr/bin/env python

#
# conv.py
#

try:
    from lxml import etree
except ImportError:
    import xml.etree.ElementTree as etree
import sys
from optparse import OptionParser
from pypann import *

def parse_config(filename):
    try:
        tree = etree.parse(filename)
    except IOError:
        print "File {0} no found".format(filename)
        sys.exit(-1)

    try:
        cfg = Attributes()
        cfg.net = Attributes()
        cfg.lms = Attributes()
        cfg.faces = Attributes()
        cfg.net.layers = []
        for l in tree.findall("net/layer"):
            cfg.net.layers.append(int(l.text))
        cfg.net.density              = tree.findtext("net/density", 0.5)
        cfg.net.window_height        = tree.findtext("net/window_height", 5)
        cfg.net.window_width         = tree.findtext("net/window_width", 5)
        cfg.net.window_vert_overlap  = tree.findtext("net/window_vert_overlap", 3)
        cfg.net.window_horiz_overlap = tree.findtext("net/window_horiz_overlap", 3)
        cfg.lms.learning_rate        = tree.findtext("lms/learning_rate", 0.2)
        cfg.lms.annealing_tsc        = tree.findtext("lms/annealing_tsc", 20)
        cfg.lms.epochs               = tree.findtext("lms/epochs", 10)
        cfg.faces.men                = tree.findtext("faces/men", 2)
    except AssertionError:
        print "Broken configuration"
        sys.exit(-1)
    return cfg

def parse_args(argv):
    parser = OptionParser(
            usage="Usage: %prog [-c filename] -m <metadata file> [options]",
            version="%prog 0.1")
    parser.add_option("-c", "--config",
            dest="configfile",
            default="config.xml",
            help="Path to configuration file\nDefault: %default")
    parser.add_option("-m", "--m",
            dest="metadata",
            help="Metadata file for faces")
    (opts, args) = parser.parse_args(argv)
    if not opts.metadata:
        parser.print_help()
        sys.exit(-1)
    return (opts, args)

def build_net(cfg):
    net = convolutional_network(
        cfg.net.layers,
        cfg.net.density,
        cfg.net.window_height,
        cfg.net.window_width,
        cfg.net.window_horiz_overlap,
        cfg.net.window_vert_overlap,
        input_tf  = Tanh,
        conv_tf   = Tanh,
        ss_tf     = Tanh,
        output_tf = Tanh)
#TODO add out layer

def read_images(mfile):
    return []

if __name__ == "__main__":
    (opts, args) = parse_args(sys.argv[1:])
    config = parse_config(opts.configfile)
    net = build_net(config)

