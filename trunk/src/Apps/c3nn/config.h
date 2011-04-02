#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>

#include "pann-shit.h"

using namespace std;
using namespace pann;

typedef unsigned IdT;

struct WeightRandomizationConfigT {
    Float min;
    Float max;
    unsigned random_seed;

    WeightRandomizationConfigT() : min(-0.1), max(+0.1), random_seed(0) {};
    void print() const {
        cout<<"WeightRandomization:\n"<<" min: "<<min<<"\n max: "<<max<<"\nseed: "<<random_seed<<"\n";
    };
};

struct LmsConfigT {
    Float learning_rate;
    unsigned annealing_tsc;
    unsigned epochs;

    LmsConfigT() : learning_rate(0.3), annealing_tsc(100), epochs(200) {};
    void print() const {
        cout<<"LMS:"
            <<"\n learning_rate: "<<learning_rate
            <<"\n annealing_tsc: "<<annealing_tsc
            <<"\n epochs: "<<epochs<<"\n";
    };
};

struct FaceConfigT {
    string path;
    unsigned man;
    unsigned position;
};

struct FacesConfigT {
    vector<FaceConfigT> faces;
    unsigned random_seed;
    unsigned men;
    Float train_percent;
    unsigned report_frequency;
    Float stop_error;

    FacesConfigT() : random_seed(0), train_percent(60.0), report_frequency(1), stop_error(0.01) {};
    void print() const {
        cout<<"Faces:"
            <<"\n faces count: "<<faces.size()
            <<"\n random_seed: "<<random_seed
            <<"\n train_percent: "<<train_percent
            <<"\n report_frequency: "<<report_frequency
            <<"\n stop_error: "<<stop_error<<"\n";
    };
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
    unsigned random_seed;
    unsigned threads_count;

    NetConfigT() : random_seed(0), threads_count(0) {};

    void print() const {
        cout<<"Net:\n seed:"<<random_seed<<"\n threads: "<<threads_count<<"\n";
        for(vector<PlaneConfigT>::const_iterator it = planes.begin(); it != planes.end(); ++it)
            it->print();
        for(vector<ConnectionConfigT>::const_iterator it = connections.begin(); it != connections.end(); ++it)
            it->print();
    };
};

struct ConfigT {
    vector<NetConfigT> nets;
    WeightRandomizationConfigT weight_randomization;
    LmsConfigT lms;
    FacesConfigT faces;

    void print() const {
        for(vector<NetConfigT>::const_iterator it = nets.begin(); it != nets.end(); ++it)
            it->print();
        weight_randomization.print();
        lms.print();
        faces.print();
    };
};

struct FaceT {
    unsigned man;
    unsigned position;
    Image * img;
};

ConfigT configure(const char * filename);
vector<FaceT> make_faces(ConfigT & cfg);
vector<NetPtr> make_nets(ConfigT & cfg);

#endif // CONFIG_H
