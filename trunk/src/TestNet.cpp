//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Neuron.h"
#include "ActivationFunction.h"

using namespace std;
using namespace boost;
using namespace pann;

int main()
{
    ActivationFunction::Linear defaultFunction;
    Neuron n(defaultFunction);

    n["ilf"] = (int)10;
    cout<<"n[ilf] = "<<setprecision(5)<<(float)any_cast<int>(n["ilf"])<<endl;
    cout<<"Linear.f() = "<<n.activationValue<<endl;

    return 0;
}

