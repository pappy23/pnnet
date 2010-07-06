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

    WeightRandomizationConfigT() : min(-0.1), max(+0.1) {};
    void print() const {
        cout<<"WeightRandomization:\n"<<" min: "<<min<<"\n max: "<<max<<"\n";
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

struct FacesConfigT {
    string database_path;
    unsigned random_seed;
    unsigned men;
    Float train_percent;
    unsigned report_frequency;
    Float stop_error;

    FacesConfigT() : random_seed(0), train_percent(60.0), report_frequency(1), stop_error(0.01) {};
    void print() const {
        cout<<"Faces:"
            <<"\n random_seed: "<<random_seed
            <<"\n train_percent: "<<train_percent
            <<"\n report_frequency: "<<report_frequency
            <<"\n stop_error: "<<stop_error<<"\n";
    };
};

struct PlaneConfigT {
    IdT id;
    bool is_input;
    unsigned width;
    unsigned height;
    unsigned window_width;
    unsigned window_height;

    PlaneConfigT() : is_input(false) {};
    void print() const {
        cout<<" Plane:"
            <<"\n  id: "<<id
            <<"\n  is_input: "<<is_input
            <<"\n  width: "<<width
            <<"\n  height: "<<height
            <<"\n  window_width: "<<window_width
            <<"\n  window_height: "<<window_height<<"\n";
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
    void print() const {
        cout<<"Net:\n";
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

void configure(const char * filename);

#endif // CONFIG_H
