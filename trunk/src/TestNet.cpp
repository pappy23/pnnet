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
    /*
     * Net of 4 neurons
     *      +      <--- output
     *     / \
     *    +   +
     *     \ /
     *      +      <--- input
     */
    Net net;
    int nInput  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nWork1  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nWork2  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nOutput = net.addNeuron(ActivationFunction::Linear::Instance());
    net.addConnection(nInput, nWork1);
    net.addConnection(nInput, nWork2);
    net.addConnection(nWork1, nOutput);
    net.addConnection(nWork2, nOutput);
    
    //Link deletion test
    net.addConnection(nInput, nOutput);
    net.delConnection(nInput, nOutput);
    //net.delConnection(nInput, nOutput);
    
    //Neuron deletion test
    //net.delNeuron(nWork2);

    return 0;
}

