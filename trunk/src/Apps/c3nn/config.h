#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

#include "pann-shit.h"

using namespace std;
using namespace pann;

typedef unsigned IdT;

struct WeightRandomizationConfigT {
    Float min;
    Float max;
};

struct LmsConfigT {
    Float learning_rate;
    unsigned annealing_tsc;
    unsigned epochs;
};

struct FacesConfigT {
    string database_path;
    unsigned random_seed;
    unsigned men;
    Float train_percent;
    unsigned report_frequency;
    Float stop_error;
};

struct PlaneConfigT {
    IdT id;
    bool is_input;
    unsigned width;
    unsigned height;
    unsigned window_width;
    unsigned window_height;
};

struct ConnectionConfigT {
    IdT from;
    IdT to;
    Float density;
};

struct NetConfigT {
    vector<PlaneConfigT> planes;
    vector<ConnectionConfigT> connections;
};

struct ConfigT {
    vector<NetConfigT> nets;
    WeightRandomizationConfigT weight_randomization;
    LmsConfigT lms;
    FacesConfigT faces;
};

void parse_config(const char * filename);

#endif // CONFIG_H
