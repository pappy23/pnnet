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
    int nInput  = net.addInputNeuron();
    int nWork1  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nWork2  = net.addNeuron(ActivationFunction::Linear::Instance());
    int nOutput = net.addOutputNeuron(ActivationFunction::Linear::Instance());
    net.addConnection(nInput, nWork1);
    net.addConnection(nInput, nWork2);
    net.addConnection(nWork1, nOutput);
    net.addConnection(nWork2, nOutput);
    
    //Link deletion test
    net.addConnection(nInput, nOutput);
    net.delConnection(nInput, nOutput);
    //net.delConnection(nInput, nOutput); //raises exception
    
    //Neuron deletion test
    net.delNeuron(nWork2);

    //Maps
    vector<int> inputs = net.getInputMap();
    vector<int> outputs = net.getOutputMap();

    cout<<"Input mapping: ";
    for(vector<int>::iterator it = inputs.begin(); it != inputs.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;

    cout<<"Output mapping: ";
    for(vector<int>::iterator it = outputs.begin(); it != outputs.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;

    //Input
    vector<float> input; 
    input.push_back(1);
    net.setInput(input);

    //Test run()
    net.run();

    //Output
    cout<<"Test output: "<<net.getOutput().at(0)<<endl;

    return 0;
}

