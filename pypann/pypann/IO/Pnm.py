#
# Pnm
#

import sys
from ..Util import squash

def read_pnm(filename):
    """Reads image from PNM file

    Image format specification: http://ozviz.wasp.uwa.edu.au/~pbourke/dataformats/ppm

    Signature: f(str) -> Image"""
    with open(filename, mode="r") as f:
        if f.read(1) != 'P':
            raise IOError("Wrong magic")
        format_no = f.read(1)
        if format_no in ('1', '2', '3'): #PBM, PGM, PPM
            read_numbers = True
        elif format_no in ('4', '5', '6'):
            read_numbers = False
        else:
            raise IOError("Wrong magic")

        header = []
        if format_no not in ('1', '4'):
            total_tokens = 3 #width, height, depth
        else: #PBM
            total_tokens = 2 #width, height
        token = ""
        while len(header) < total_tokens:
            c = f.read(1)
            if c == '#':
                if token:
                    header.append(int(token))
                    token = ""
                while f.read(1) not in ('\n', '\r'):
                    pass #Skip comment until EOL
            elif c in ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9'):
                token += c
            elif c in (' ', '\n', '\r'):
                if token:
                    header.append(int(token))
                    token = ""
            else:
                raise IOError("File is broken")
        if total_tokens == 2:
            header.append(255)
        print "Header:", header

        raw_data = []
        target_size = header[0] * header[1]
        if format_no in ('3', '6'): #PPM
            target_size *= 3
        while len(raw_data) < target_size:
            if not read_numbers:
                c = f.read(1)
                if not c:
                    raise IOError("Invalid size")
                raw_data.append(ord(c))
            else:
                token = ""
                while True:
                    c = f.read(1)
                    if not c:
                        raise IOError("Invalid size")
                    if c in ('0', '1', '2', '3', '4', '5', '6', '7', '8', '9'):
                        token += c
                    elif c in (' ', '\n', '\r'):
                        break
                    else:
                        raise IOError("Invalid data")
                if token:
                    token = int(token)
                    if token > header[2]: #depth
                        raise IOError("Invalid depth")
                    raw_data.append(token)

        for x in raw_data:
            if not x:
                raise IOError("Internal error of image reader")

        return Image(header[0], header[1], squash(raw_data, 0, header[2], 0, 255))

def write_pnm(img, filename):
    """Writes image to file with automatic color detection

    If supplied img object has G and B values then result file will have
    P6 (PPM) format with RGB components. Otherwise file format will be
    grayscale P5 (PGM)

    Signature: f(Image) -> None"""
    if img.g or img.b:
        format_no = '6'
        data = []
        for i in range(img.width() * img.height()):
            data.append(img.r[i])
            data.append(img.g[i])
            data.append(img.b[i])
    else:
        format_no = '5'
        data = img.r
    with open(filename, "wb") as f:
        f.write('P' + format_no + '\n' + str(img.width()) + ' ' + str(img.height()) + '\n255\n')
        for c in data:
            f.write(chr(c))

