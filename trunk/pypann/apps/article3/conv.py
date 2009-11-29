#!/usr/bin/env python

#
# conv.py
#

#TODO: Documentation

try:
    from lxml import etree
except ImportError:
    import xml.etree.ElementTree as etree
import sys
from random import shuffle
from optparse import OptionParser
from pypann import *

def parse_config(cfile):
    #TODO: use XML DOM
    try:
        tree = etree.parse(cfile)
    except IOError:
        print "File {0} not found".format(cfile)
        sys.exit(-1)

    try:
        cfg = Attributes()
        cfg.net = Attributes()
        cfg.weight_randomization = Attributes()
        cfg.lms = Attributes()
        cfg.faces = Attributes()
        cfg.net.layers = []
        for l in tree.findall("net/layer"):
            cfg.net.layers.append(int(l.text))
        cfg.net.density              = float(tree.findtext("net/density", 0.5))
        cfg.net.window_height        = int(tree.findtext("net/window_height", 5))
        cfg.net.window_width         = int(tree.findtext("net/window_width", 5))
        cfg.net.window_vert_overlap  = int(tree.findtext("net/window_vert_overlap", 3))
        cfg.net.window_horiz_overlap = int(tree.findtext("net/window_horiz_overlap", 3))
        cfg.weight_randomization.min = float(tree.findtext("weight_randomization/min", -0.1))
        cfg.weight_randomization.max = float(tree.findtext("weight_randomization/max", +0.1))
        cfg.lms.learning_rate        = float(tree.findtext("lms/learning_rate", 0.2))
        cfg.lms.annealing_tsc        = float(tree.findtext("lms/annealing_tsc", 20))
        cfg.lms.epochs               = int(tree.findtext("lms/epochs", 10))
        cfg.faces.men                = int(tree.findtext("faces/men", 10))
        cfg.faces.train_percent      = int(tree.findtext("faces/train_percent", 60))
        cfg.faces.report_frequency   = int(tree.findtext("faces/report_frequency", 1))
        cfg.faces.stop_error         = float(tree.findtext("faces/stop_error", 0.3))
    except:
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
        input_tf  = TF.Tanh,
        conv_tf   = TF.Tanh,
        ss_tf     = TF.Tanh,
        output_tf = TF.Tanh)
    net.run(Runners.null)
    for i in range(cfg.faces.men):
        n = PyramidalNeuron(TF.Linear)
        for j in net._cache.layers[-1]:
            net.connect(j, n, Weight(1))
    net.weight_randomization_attributes = Attributes()
    net.weight_randomization_attributes.min = cfg.weight_randomization.min
    net.weight_randomization_attributes.max = cfg.weight_randomization.max
    net.run(Runners.randomize_weights_gauss)
    lms(net, [])
    net.lms_attributes.learning_rate = cfg.lms.learning_rate
    net.lms_attributes.annealing_tsc = cfg.lms.annealing_tsc
    return net

def read_images(mfile):
    try:
        tree = etree.parse(mfile)
    except IOError:
        print "File {0} not found".format(mfile)
        sys.exit(-1)

    result = []
    for ximg in tree.findall("face"):
        try: #FIXME
            img = read_pnm(tree.findtext("directory") + "/" + ximg.findtext("file")) 
#Image(3,3, [1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9])
            img.man = int(ximg.findtext("man"))
            img.position = int(ximg.findtext("position"))
            img.shift = int(ximg.findtext("shift"))
            img.noise = int(ximg.findtext("noise"))
            result.append(img)
        except IOError:
            print "Error loading {0}".format(ximg.findtext("file"))
        except:
            print "Broken metafile"
            sys.exit(-1)
    return result

def config_to_string(cfg):
    s = ""
    for r in cfg.__dict__:
        s = s + r + "\n"
        for a in cfg.__dict__[r].__dict__:
            s = s + " " + a + " = " + str(cfg.__dict__[r].__dict__[a]) + "\n"
    return s

def image_to_train_pattern(img, cfg):
    #assert img.g == [] FIXME
    #assert img.b == []
    input = squash(img.r, 0,255, -1.8,+1.8)
    output = [-1.8] * cfg.faces.men
    try:
        output[img.man] = +1.8
    except:
        pass
    return (input, output)

if __name__ == "__main__":
    (opts, args) = parse_args(sys.argv[1:])

    config = parse_config(opts.configfile)
    print "Config:", config_to_string(config)

    net = build_net(config)
    print "Net cache:"
    for l in net._cache.layers:
        print len(l),
    print

    orl = read_images(opts.metadata)
    print "Loaded {0} images".format(len(orl))

    all_data = []
    for img in orl:
        if img.man < config.faces.men:
            all_data.append(image_to_train_pattern(img, config))
    shuffle(all_data)
    (train_data, test_data) = divide(all_data, config.faces.train_percent)
    print "Train/Test: {0}/{1}".format(len(train_data), len(test_data))

    print "Training for {0} epochs... (using {1} threads)".format(config.lms.epochs, net.worker_threads_count)
    for i in range(config.lms.epochs):
        shuffle(train_data)
        train_error = mse(lms(net, train_data))
        test_error = mse(test(net, test_data))
        if not i % config.faces.report_frequency:
            print "{0}\t{1}\t{2}".format(i, train_error, test_error)
        if test_error < config.faces.stop_error:
            break
    print "Training finished"
#TODO: detailed test
