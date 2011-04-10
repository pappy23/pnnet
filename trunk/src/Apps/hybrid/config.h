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

    void print() const {
        faces.print();
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

ConfigT configure(const char * filename);
map<unsigned, FaceT> make_faces(ConfigT & cfg);
void make_datasets(map<unsigned, DatasetT> & result, ConfigT & cfg, map<unsigned, FaceT> & faces);

#endif // CONFIG_H
