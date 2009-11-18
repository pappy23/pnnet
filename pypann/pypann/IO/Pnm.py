#
# Pnm
#

#TODO: use NumPy
#http://ru.wikipedia.org/wiki/Portable_anymap
#http://docs.python.org/tutorial/inputoutput.html

def read_pnm(filename):
    return []

def write_pnm(filename, format = "P5"):
    pass

def write_pbm(filename, binary = True):
    if binary:
        write_pnm(filename, "P4")
    else:
        write_pnm(filename, "P1")

def write_pgm(filename, binary = True):
    if binary:
        write_pnm(filename, "P5")
    else:
        write_pnm(filename, "P2")

def write_ppm(filename, binary = True):
    if binary:
        write_pnm(filename, "P6")
    else:
        write_pnm(filename, "P3")
