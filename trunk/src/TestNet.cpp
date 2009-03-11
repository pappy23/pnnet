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
    net.setThreadCount(0);
    int nInput  = net.addInputNeuron();
    int nWork1  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nWork2  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nOutput = net.addOutputNeuron(ActivationFunction::Linear::Instance());
    net.addConnection(nInput, nWork1, 0.5);
    net.addConnection(nInput, nWork2);
    net.addConnection(nWork1, nOutput);
    net.addConnection(nWork2, nOutput);
    
    //Input
    vector<FLOAT> input;
    input.push_back(1);
    net.setInput(input);

    //Test run()
    net.run(&(FeedforwardPropagationRunner::Instance()));

    //Debug
    {
    ostringstream ost;
    net.printDebugInfo(ost);
    //cout<<ost.str();
    }

    //Output
    cout<<"Test output: "<<net.getOutput().at(0)<<endl;

    return 0;
}

