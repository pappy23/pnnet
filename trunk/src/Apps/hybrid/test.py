#!/usr/bin/env python

import xmlrpclib

if __name__ == "__main__":

    # Create an object to represent our server.
    server = xmlrpclib.Server('http://127.0.0.1:8888')

    # Ask about available nets
    result = map(server.nets.get_net, server.nets.get_id_list())
    print result



    result = server.faces.get_count()
    result = server.datasets.get_dataset(1)
    result = server.datasets.get_id_list()
    result = server.faces.get_face(10)
    result = server.faces.get_id_list()
    result = server.nets.rename(1, 'new name')
    result = server.nets.load(1)
    result = server.nets.save(1)
#    result = server.nets.get_size(1)
#    print result
