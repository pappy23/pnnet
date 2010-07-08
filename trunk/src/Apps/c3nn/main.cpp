
#include "pann-shit.h"
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

#include "config.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char ** argv)
{
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

    vector<FaceT> orl;
    make_faces(cfg, orl);
    vector<NetPtr> nets = make_nets(cfg);
    Storage::save<Storage::xml_out>(nets[0], "test_net.xml");

    return 0;
}; //main

