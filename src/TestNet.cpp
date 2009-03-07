//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "Net.h"
#include "Exception.h"

using namespace std;
using namespace pann;
using boost::any_cast;

int main()
{
    Net net;
    int nid = net.addNeuron(ActivationFunction::Linear::Instance());
    Neuron& n = net.getNeuron(nid);

    try
    {
        throw Exception::ElementExists()<<"test1"<<5.678<<"\n"<<5<<6<<"Test\n";
    } catch(Exception::Base e)
    {
        cout<<e.text();
    }

    n["ilf"] = (int)10;
    cout<<"n[ilf] = "<<setprecision(5)<<(float)any_cast<int>(n["ilf"])<<endl;
    cout<<"Linear.f() = "<<n.activationValue<<endl;

    return 0;
}

