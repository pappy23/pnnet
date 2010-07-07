
#include <iostream>
#include <fstream>
#include <cstring>
#include <boost/lexical_cast.hpp>

#include "pann.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "config.h"

using namespace std;
using namespace pann;
using namespace rapidxml;
using boost::lexical_cast;

const unsigned MAX_FILESIZE = 10000;

ConfigT configure(const char * filename)
{
    ConfigT config;

    rapidxml::file<> xmlfile(filename);
    xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    xml_node<> *root = doc.first_node("config");
    for(xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
        if(!strcmp(child->name(), "net")) {
            NetConfigT net_config;
            for(xml_node<> *item = child->first_node(); item; item = item->next_sibling()) {
                if(!strcmp(item->name(), "plane")) {
                    PlaneConfigT plane_config;
                    for(xml_attribute<> *attr = item->first_attribute(); attr; attr = attr->next_attribute()) {
                        if(!strcmp(attr->name(), "id")) {
                            plane_config.id = lexical_cast<IdT>(attr->value());
                        }
                        if(!strcmp(attr->name(), "width")) {
                            plane_config.width = lexical_cast<unsigned>(attr->value());
                        }
                        if(!strcmp(attr->name(), "height")) {
                            plane_config.height = lexical_cast<unsigned>(attr->value());
                        }
                        if(!strcmp(attr->name(), "window_width")) {
                            plane_config.window_width = lexical_cast<unsigned>(attr->value());
                        }
                        if(!strcmp(attr->name(), "window_height")) {
                            plane_config.window_height = lexical_cast<unsigned>(attr->value());
                        }
                        if(!strcmp(attr->name(), "conv")) {
                            plane_config.is_conv = (!strcmp(attr->value(), "true"));
                        }
                    }
                    net_config.planes.push_back(plane_config);
                }
                if(!strcmp(item->name(), "connection")) {
                    ConnectionConfigT connection_config;
                    for(xml_attribute<> *attr = item->first_attribute(); attr; attr = attr->next_attribute()) {
                        if(!strcmp(attr->name(), "from")) {
                            connection_config.from = lexical_cast<IdT>(attr->value());
                        }
                        if(!strcmp(attr->name(), "to")) {
                            connection_config.to = lexical_cast<IdT>(attr->value());
                        }
                        if(!strcmp(attr->name(), "density")) {
                            connection_config.density = lexical_cast<Float>(attr->value());
                        }
                    }
                    net_config.connections.push_back(connection_config);
                }
            }
            config.nets.push_back(net_config);
        }
        if(!strcmp(child->name(), "weight_randomization")) {
            for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                if(!strcmp(attr->name(), "min")) {
                    config.weight_randomization.min = lexical_cast<Float>(attr->value());
                }
                if(!strcmp(attr->name(), "max")) {
                    config.weight_randomization.max = lexical_cast<Float>(attr->value());
                }
            }
        }
        if(!strcmp(child->name(), "lms")) {
            for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                if(!strcmp(attr->name(), "learning_rate")) {
                    config.lms.learning_rate = lexical_cast<Float>(attr->value());
                }
                if(!strcmp(attr->name(), "annealing_tsc")) {
                    config.lms.annealing_tsc = lexical_cast<unsigned>(attr->value());
                }
                if(!strcmp(attr->name(), "epochs")) {
                    config.lms.epochs = lexical_cast<unsigned>(attr->value());
                }
            }
        }
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
                if(!strcmp(attr->name(), "seed")) {
                    config.faces.random_seed = lexical_cast<unsigned>(attr->value());
                }
                if(!strcmp(attr->name(), "men")) {
                    config.faces.men = lexical_cast<unsigned>(attr->value());
                }
                if(!strcmp(attr->name(), "train_percent")) {
                    config.faces.train_percent = lexical_cast<Float>(attr->value());
                }
                if(!strcmp(attr->name(), "report_frequency")) {
                    config.faces.report_frequency = lexical_cast<unsigned>(attr->value());
                }
                if(!strcmp(attr->name(), "stop_error")) {
                    config.faces.stop_error = lexical_cast<Float>(attr->value());
                }
            }
        }
    }

    return config;
}; //configure

void make_faces(ConfigT & cfg, vector<FaceT> & result)
{
    cout<<"Reading images from disk...\n";
    for(vector<FaceConfigT>::iterator it = cfg.faces.faces.begin(); it != cfg.faces.faces.end(); ++it) {
        try {
            FaceT face;
            face.img = new Image(ImageIo::readImage(it->path));
            face.man = it->man;
            face.position = it->position;
            result.push_back(face);
        } catch (Exception & e) {
            cout<<"Error reading image '"<<it->path<<"'\n";
        }
    }

    cout<<"Read "<<result.size()<<" images\n";

}; //make_faces

vector<NetPtr> make_nets(ConfigT & cfg)
{
    vector<NetPtr> result;

    for(vector<NetConfigT>::const_iterator net_iter = cfg.nets.begin(); net_iter != cfg.nets.end(); ++net_iter) {
        net_data_t net_data;
        for(vector<PlaneConfigT>::const_iterator plane_iter = net_iter->planes.begin(); plane_iter != net_iter->planes.end(); ++plane_iter) {
            plane_data_t plane_data;
            plane_data.width = plane_iter->width;
            plane_data.height = plane_iter->height;
            plane_data.window_width = plane_iter->window_width;
            plane_data.window_height = plane_iter->window_height;
            plane_data.tf = TanH::Instance();
            net_data.planes.push_back(make_plane(plane_data, plane_iter->is_conv));
        }
        result.push_back(make_net(net_data));
    }

    return result;
}; //make_nets
