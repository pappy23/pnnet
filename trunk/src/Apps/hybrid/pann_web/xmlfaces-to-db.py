#!/usr/bin/env python


try:
    from lxml import etree
except ImportError:
    import xml.etree.ElementTree as etree
import sys
import sqlite3
from optparse import OptionParser


def sql(sqlQueries):
    connection = sqlite3.connect('db.sqlite3')
    cursor = connection.cursor()
    for query in sqlQueries:
        cursor.execute(query)
    connection.commit()

def parse_args(argv):
    parser = OptionParser(
            usage="Usage: %prog -m <metadata file>",
            version="%prog 0.1")
    parser.add_option("-m", "--m",
            dest="metadata",
            help="Metadata file for faces")
    (opts, args) = parser.parse_args(argv)
    if not opts.metadata:
        parser.print_help()
        sys.exit(-1)
    return (opts, args)

def read_images(mfile):
    try:
        tree = etree.parse(mfile)
    except IOError:
        print "File {0} not found".format(mfile)
        sys.exit(-1)

    counter = 1
    cmd = []
    for ximg in tree.findall("face"):
        try:
            img_path = tree.findtext("directory") + "/" + ximg.findtext("file")
            img_man = int(ximg.findtext("man"))
            img_position = int(ximg.findtext("position"))
            cmd = ["insert into main_face(id, man, position, path) values ("+counter.__str__()+", "+img_man.__str__()+","+img_position.__str__()+",'"+img_path+"');"]
            counter+=1
            sql(cmd)
        except IOError:
            print "Error loading {0}".format(ximg.findtext("file"))
        except:
            print "Broken metafile"
            sys.exit(-1)

def clear_table():
    sql(["""delete from main_face;"""]);

if __name__ == "__main__":
    (opts, args) = parse_args(sys.argv[1:])

    clear_table()
    read_images(opts.metadata)

