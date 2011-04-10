#!/usr/bin/env python

import xmlrpclib

if __name__ == "__main__":

    # Create an object to represent our server.
    server = xmlrpclib.Server('http://127.0.0.1:8888')
    result = server.datasets.get_dataset(1)
    print result

    result = server.faces.get_count()
    # Call the server and get our result.
    print "Faces loaded:", result

