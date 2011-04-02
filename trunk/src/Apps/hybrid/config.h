#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>

#include "pann-shit.h"

using namespace std;
using namespace pann;

typedef unsigned IdT;

struct FaceConfigT {
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
    unsigned man;
    unsigned position;
    string path;
    Image * img;
};

ConfigT configure(const char * filename);
vector<FaceT> make_faces(ConfigT & cfg);

#endif // CONFIG_H
