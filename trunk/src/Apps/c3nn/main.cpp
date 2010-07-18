
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

#include "pann-shit.h"
#include "config.h"
#include "util.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char ** argv)
{
    random_seed(time(0));

    if(argc < 2) {
        cout<<"Usage: "<<argv[0]<<" <config-file-path>"<<endl;
        return -1;
    }

    ConfigT cfg;
    try {
        cfg = configure(argv[1]);
    } catch (std::exception e) {
        cout<<"Error while reading configuration data\n"<<e.what()<<endl;
        return -1;
    }

    cfg.print();

//    vector<FaceT> orl = make_faces(cfg);
    cout<<"Random number: "<<rand()<<"\n";
    vector<NetPtr> nets = make_nets(cfg);
    trace(nets[0]);
    cout<<"Random number: "<<rand()<<"\n";

    TrainPattern tmp(4, 1);
    for(unsigned i = 0; i < 4; ++i) {
        tmp.input()[i] = 1;
    }

    nets[0]->set_input(tmp.input());
    nets[0]->run(FeedforwardPropagationRunner::Instance());
    nets[0]->get_output(tmp.actual_output()); //actual output
    cout<<tmp.input()[0]<<" "<<tmp.actual_output()[0]<<endl;

    return 0;
}; //main

