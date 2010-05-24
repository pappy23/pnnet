
#include "pann-shit.h"
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char ** argv)
{
    vector<unsigned> layers;
    layers += 1,2;
    NetPtr net = make_convnet(layers, 1.0, 2, 2, 1, 1, Linear::Instance(), TanH::Instance(), TanH::Instance(), TanH::Instance());

    net->run(FeedforwardPropagationRunner::Instance());



    return 0;
}; //main

