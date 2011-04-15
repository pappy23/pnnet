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

ConfigT configure(const char * filename);
map<unsigned, FaceT> make_faces(ConfigT & cfg);
void make_datasets(map<unsigned, DatasetT> & result, ConfigT & cfg, map<unsigned, FaceT> & faces);
void make_nets(map<unsigned, NetT> & result, ConfigT & cfg);
void save_nets_info(map<unsigned, NetT> & nets, ConfigT & cfg);

#endif // CONFIG_H
