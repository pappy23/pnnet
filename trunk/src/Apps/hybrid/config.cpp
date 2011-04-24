
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
        if(!strcmp(child->name(), "gcnn")) {
            config.gcnn_nets_filename = child->first_node("database")->value();
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
        f<<"\n<net>\n  <id>"<<it->first<<"</id>\n  <name>"<<it->second.name<<"</name>\n  <file>"<<it->second.path<<"</file>\n</net>\n";
    }

    f<<"</metadata>\n";
    f.close();
}; //save_nets

void make_nets_from_config(map<unsigned, NetT> & result, ConfigT & cfg)
{
    vector<NetConfigT> nets;

    rapidxml::file<> xmlfile(cfg.gcnn_nets_filename.c_str());
    xml_document<> doc;
    doc.parse<0>(xmlfile.data());

    xml_node<> *root = doc.first_node("config");
    for(xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
        if(!strcmp(child->name(), "net")) {
            NetConfigT net_config;
            for(xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute()) {
                if(!strcmp(attr->name(), "name")) {
                    net_config.name = attr->value();
                }
            }
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
            nets.push_back(net_config);
            cout<<" found net name="<<net_config.name<<endl;
        }
    }

    //Find next free id
    unsigned id = 0;
    for(map<unsigned, NetT>::iterator it = result.begin(); it != result.end(); ++it)
        if(it->first > id)
            id = it->first;
    id++;

    cout<<"ID = "<<id<<endl;

    random_seed(42);
    cout<<"r = "<<rand01()<<endl;

    for(vector<NetConfigT>::const_iterator net_iter = nets.begin(); net_iter != nets.end(); ++net_iter) {
        net_data_t net_data;
        map<unsigned, unsigned> plane_id;
        unsigned cur_plane_id = 0;
        for(vector<PlaneConfigT>::const_iterator plane_iter = net_iter->planes.begin(); plane_iter != net_iter->planes.end(); ++plane_iter) {
            plane_data_t plane_data;
            plane_data.width = plane_iter->width;
            plane_data.height = plane_iter->height;
            plane_data.window_width = plane_iter->window_width;
            plane_data.window_height = plane_iter->window_height;
            plane_data.tf = TanH::Instance();
            plane_t p = make_plane(plane_data, plane_iter->is_conv);
            //net_data.planes.push_back(make_plane(plane_data, plane_iter->is_conv));
            net_data.planes.push_back(p);
            plane_id[plane_iter->id] = cur_plane_id++;
        }

        net_data.connection_matrix.resize(boost::extents[cur_plane_id][cur_plane_id]);
        for(unsigned i = 0; i < cur_plane_id; ++i)
            for(unsigned j = 0; j < cur_plane_id; ++j)
                net_data.connection_matrix[i][j] = 0.0;
        for(vector<ConnectionConfigT>::const_iterator conn_iter = net_iter->connections.begin(); conn_iter != net_iter->connections.end(); ++conn_iter) {
            net_data.connection_matrix[plane_id[conn_iter->from]][plane_id[conn_iter->to]] = conn_iter->density;
        }

        cout<<" building net #"<<id<<" name="<<net_iter->name<<endl;
        NetPtr pnet = make_net(net_data);
        cout<<" done!"<<endl;

        result[id].id = id;
        result[id].name = net_iter->name;
        result[id].path = lexical_cast<string>(id) + ".net";
        result[id].actual = false;
        result[id].p = pnet;
        id++;
        cout<<" ok\n";
   }

    //Update net list on disk
    save_nets_info(result, cfg);

}; //make_nets_from_config

