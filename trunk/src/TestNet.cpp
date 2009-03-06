//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "Neuron.h"

using namespace std;
using namespace boost;
using namespace pann;

int main()
{
    vector<Neuron> v; 
    v.push_back(Neuron(ActivationFunction::Linear::Instance()));

    v[0]["ilf"] = (int)10;
    cout<<"n[ilf] = "<<setprecision(5)<<(float)any_cast<int>(v[0]["ilf"])<<endl;
    cout<<"Linear.f() = "<<v[0].activationValue<<endl;

    return 0;
}

