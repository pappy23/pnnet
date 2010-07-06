
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

    configure(argv[1]);

    return 0;
}; //main

