#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>

#include "pann-shit.h"

using namespace std;
using namespace pann;

typedef unsigned IdT;

struct FaceConfigT {
    unsigned id;
    string path;
    unsigned man;
    unsigned position;
};

struct FacesConfigT {
    vector<FaceConfigT> faces;
    unsigned men;

    FacesConfigT() {};
    void print() const {
        cout<<"Faces:"
            <<"\n faces count: "<<faces.size()<<"\n";
    };
};

struct ConfigT {
    FacesConfigT faces;
    int rpc_port;
    string net_list_path;
    string net_list_path_base;
    string gcnn_nets_filename;

    void print() const {
        faces.print();
        cout<<"RPC port: "<<rpc_port
            <<"\n Path to network list: "<<net_list_path<<"\n";
    };
};

struct FaceT {
    unsigned id;
    unsigned man;
    unsigned position;
    string path;
    Image * img;
};

struct DatasetT {
    unsigned id;
    string name;
    vector<unsigned> face_ids;
    TrainData td;
};

struct NetT {
    unsigned id;
    string name;
    string path;
    bool actual;
    NetPtr p;
};

struct PlaneConfigT {
    IdT id;
    unsigned width;
    unsigned height;
    unsigned window_width;
    unsigned window_height;
    bool is_conv;

    PlaneConfigT() : is_conv(false) {};

    void print() const {
        cout<<" Plane:"
            <<"\n  id: "<<id
            <<"\n  width: "<<width
            <<"\n  height: "<<height
            <<"\n  window_width: "<<window_width
            <<"\n  window_height: "<<window_height
            <<"\n  is_conv: "<<is_conv<<"\n";
    };
};

struct ConnectionConfigT {
    IdT from;
    IdT to;
    Float density;

    ConnectionConfigT() : density(1.0) {};
    void print() const {
        cout<<" Connection:"
            <<"\n  from: "<<from
            <<"\n  to: "<<to
            <<"\n  density: "<<density<<"\n";
    };
};

struct NetConfigT {
    vector<PlaneConfigT> planes;
    vector<ConnectionConfigT> connections;
    string name;

    void print() const {
        cout<<"Name: "<<name<<endl;
        for(vector<PlaneConfigT>::const_iterator it = planes.begin(); it != planes.end(); ++it)
            it->print();
        for(vector<ConnectionConfigT>::const_iterator it = connections.begin(); it != connections.end(); ++it)
            it->print();
    };
};

ConfigT configure(const char * filename);
map<unsigned, FaceT> make_faces(ConfigT & cfg);
void make_datasets(map<unsigned, DatasetT> & result, ConfigT & cfg, map<unsigned, FaceT> & faces);
void make_nets(map<unsigned, NetT> & result, ConfigT & cfg);
void save_nets_info(map<unsigned, NetT> & nets, ConfigT & cfg);
void make_nets_from_config(map<unsigned, NetT> & result, ConfigT & cfg);

#endif // CONFIG_H
