//NeuronTest.cpp

#include "Neuron.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    Neuron n(1);
    n["ilf"] = (int)10;
    cout<<"n[ilf] = "<<setprecision(5)<<(float)any_cast<int>(n["ilf"])<<endl;

    return 0;
}

