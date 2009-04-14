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

    Storage::save<Storage::bin_out>(net, "test_conv.bin");

    return 0;
}

