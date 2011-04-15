
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

    unsigned id_counter = 1;
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
                            face_config.id = id_counter++;
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
        if(!strcmp(child->name(), "nets")) {
            config.net_list_path = child->first_node("database")->value();
        }
    }

    return config;
}; //configure

map<unsigned, FaceT> make_faces(ConfigT & cfg)
{
    map<unsigned, FaceT> result;

    cout<<"Reading images from disk...\n";
    for(vector<FaceConfigT>::iterator it = cfg.faces.faces.begin(); it != cfg.faces.faces.end(); ++it) {
        try {
            FaceT face;
            face.id = it->id;
            face.img = new Image(ImageIo::readImage(it->path));
            face.man = it->man;
            face.position = it->position;
            face.path = it->path;
            result[face.id] = face;
        } catch (Exception & e) {
            cout<<"Error reading image '"<<it->path<<"'\n";
        }
    }

    cout<<"Read "<<result.size()<<" images\n";

    return result;
}; //make_faces

void make_datasets(map<unsigned, DatasetT> & result, ConfigT & cfg, map<unsigned, FaceT> & faces)
{
    //This function is stub; we just divide all data into two datasets

    result[1].name = "all faces";
    result[2].name = "learning dataset; men 1-5, 60%";
    result[3].name = "test dataset; men 1-5, 40%";

    unsigned use_man = 5;

    for(map<unsigned, FaceT>::iterator it = faces.begin(); it != faces.end(); ++it) {
        result[1].face_ids.push_back(it->first);
        result[1].td.push_back(imgm2tp(it->second, 40)); //all faces
    }
    shuffle(result[1].td);

    vector<unsigned> ids;
    for(map<unsigned, FaceT>::iterator it = faces.begin(); it != faces.end(); ++it) {
        if(it->second.man > use_man)
            continue;
        ids.push_back(it->first);
    }
    shuffle(ids);

    pair<vector<unsigned>, vector<unsigned> > bunch = divide(ids, 100 - 60);
    result[2].face_ids = bunch.first;
    result[3].face_ids = bunch.second;

    for(unsigned i = 0; i < result[2].face_ids.size(); ++i) {
        result[2].td.push_back(imgm2tp(faces[result[2].face_ids[i]], use_man));
    }

    for(unsigned i = 0; i < result[3].face_ids.size(); ++i) {
        result[3].td.push_back(imgm2tp(faces[result[3].face_ids[i]], use_man));
    }

    cout<<"Train/test: "<<result[2].td.size()<<"/"<<result[3].td.size()<<"\n";

    cout<<"Datasets:\n";
    for(map<unsigned, DatasetT>::iterator it = result.begin(); it != result.end(); ++it) {
        cout<<it->first<<"\t"<<it->second.name<<"\t"<<it->second.td.size()<<endl;
        it->second.id = it->first;
    }

}; //make_datasets

void make_nets(map<unsigned, NetT> & result, ConfigT & cfg)
{
    cout<<"Loading information about available neural networks...\n";

    rapidxml::file<> xmlfile(cfg.net_list_path.c_str());
    xml_document<> doc;
    doc.parse<0>(xmlfile.data());
    xml_node<> *mroot = doc.first_node("metadata");
    string path_base;
    path_base.append(mroot->first_node("directory")->value());
    cfg.net_list_path_base = path_base;
    path_base.append("/");
    cout<<"Path base: "<<path_base<<endl;
    for(xml_node<> * net_node = mroot->first_node(); net_node; net_node = net_node->next_sibling()) {
        if(!strcmp(net_node->name(), "net")) {
            unsigned id = lexical_cast<unsigned>(net_node->first_node("id")->value());
            result[id].id = id;
            result[id].path.append(net_node->first_node("file")->value());
            result[id].actual = false;
            result[id].name = net_node->first_node("name")->value();
            cout<<"Found net id: "<<id<<" name: "<<result[id].name<<endl;
        }
    }

}; //make_nets

void save_nets_info(map<unsigned, NetT> & result, ConfigT & cfg)
{
    ofstream f;
    f.open(cfg.net_list_path.c_str());

    f<<"<metadata>\n";
    f<<"<directory>"<<cfg.net_list_path_base<<"</directory>\n";

    for(map<unsigned, NetT>::iterator it = result.begin(); it != result.end(); ++it) {
        f<<"<net>\n<id>"<<it->first<<"</id>\n<name>"<<it->second.name<<"</name>\n<file>"<<it->second.path<<"</file>\n</net>\n";
    }

    f<<"</metadata>\n";
    f.close();
}; //save_nets

