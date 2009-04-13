#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    Net& net = NetworkModel::ConvolutionalNetworkDraft();

    Storage::save<Storage::xml_out>(net, "test_net.xml");

    return 0;
}

