
#include <iostream>
#include <fstream>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "pann.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "config.h"
#include "util.h"

using namespace std;
using namespace pann;
using namespace rapidxml;
using boost::lexical_cast;

const unsigned MAX_FILESIZE = 10000;

ConfigT configure(const char * filename)
{
    ConfigT config;
    config.rpc_port = 8080;

    rapidxml::file<> xmlfile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    xml_node<> *root = doc.first_node("config");
    for(xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
        if(!strcmp(child->name(), "faces")) {
            for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                if(!strcmp(attr->name(), "database")) {
                    cout<<"Reading metadata from "<<attr->value()<<endl;
                    rapidxml::file<> xmlmetadata(attr->value());
                    xml_document<> metadata;
                    metadata.parse<0>(xmlmetadata.data());
                    xml_node<> *mroot = metadata.first_node("metadata");
                    string path_base;
                    path_base.append(mroot->first_node("directory")->value());
                    path_base.append("/");
                    cout<<"path_base: "<<path_base<<endl;
                    for(xml_node<> * face_node = mroot->first_node(); face_node; face_node = face_node->next_sibling()) {
                        if(!strcmp(face_node->name(), "face")) {
                            FaceConfigT face_config;
                            face_config.path.append(path_base);
                            face_config.path.append(face_node->first_node("file")->value());
                            face_config.man = lexical_cast<unsigned>(face_node->first_node("man")->value());
                            face_config.position = lexical_cast<unsigned>(face_node->first_node("position")->value());
                            config.faces.faces.push_back(face_config);
                        }
                    }
                }
            }
        }
        if(!strcmp(child->name(), "rpc")) {
            config.rpc_port = lexical_cast<unsigned>(child->first_node("port")->value());
        }
    }

    return config;
}; //configure

vector<FaceT> make_faces(ConfigT & cfg)
{
    vector<FaceT> result;

    cout<<"Reading images from disk...\n";
    for(vector<FaceConfigT>::iterator it = cfg.faces.faces.begin(); it != cfg.faces.faces.end(); ++it) {
        try {
            FaceT face;
            face.img = new Image(ImageIo::readImage(it->path));
            face.man = it->man;
            face.position = it->position;
            face.path = it->path;
            result.push_back(face);
        } catch (Exception & e) {
            cout<<"Error reading image '"<<it->path<<"'\n";
        }
    }

    cout<<"Read "<<result.size()<<" images\n";

    return result;
}; //make_faces

