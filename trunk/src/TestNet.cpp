//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "Net.h"

using namespace std;
using namespace pann;
using boost::any_cast;

int main()
{
    Net net;
    int nid = net.addNeuron(ActivationFunction::Linear::Instance());
    Neuron& n = net.getNeuron(nid);

    n["ilf"] = (int)10;
    cout<<"n[ilf] = "<<setprecision(5)<<(float)any_cast<int>(n["ilf"])<<endl;
    cout<<"Linear.f() = "<<n.activationValue<<endl;

    return 0;
}

