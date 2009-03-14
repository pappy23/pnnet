//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "Net.h"
#include "Storage.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    //Input
    vector<Float> input;
    input.push_back(1);

    {
        //MLP simulation
        const int layers_count = 4;
        const int neurons_count = 2000;
        const int runs_count = 100;
        const int thread_count = 1;

        Net net(thread_count);

        vector< vector<int> > layers(layers_count);
        
        layers[0].push_back(net.addInputNeuron());

        int owner = 1;
        for(int i = 1; i < layers_count - 1; i++)
            for(int j = 0; j < neurons_count; j++)
            {
                layers[i].push_back(net.addNeuron(ActivationFunction::Linear::Instance()));
                net.setNeuronOwner(layers[i][j], owner);
                if(++owner > 64)
                    owner = 1;
            }
        
        layers[layers_count - 1].push_back(net.addOutputNeuron(ActivationFunction::Linear::Instance()));

        cout<<"Neurons constructed:\n";
        for(int i = 0; i < layers.size(); i++)
            cout<<layers[i].size()<<" ";
        cout<<endl;
        
        //Connect layers
        for(int i = 0; i < layers_count - 1; i++) //layers
            for(int j = 0; j < layers[i].size(); j++) //prev layer
                for(int k = 0; k < layers[i+1].size(); k++) //next layer
                    net.addConnection(layers[i][j], layers[i+1][k], 0.5);

        cout<<"MLP ready\n";

        //Test run()
        {
            progress_timer t;
            for(int i = 0; i < runs_count; i++)
            {
                cout<<i+1<<"-th run: "; 
                cout.flush();
                {
                    progress_timer t;
                    net.setInput(input);
                    net.run(&(FeedforwardPropagationRunner::Instance()));
                }
                //Output
                cout<<"Test output: "<<net.getOutput().at(0)<<endl;
            }
            cout<<"Total: ";
        }
        
        //Serialization test
        Storage::save(net, "test_net.txt");

        //Memory consumption test
        cout<<"It's time to do memory test\n";
        sleep(20);

        for(int i = 0; i < layers.size(); i++)
            cout<<layers[i].size()<<" ";
        cout<<endl;
    }

    Net net2;
    cout<<"New net...OK\n";
    Storage::load(net2, "test_net.txt");

    //Test run()
    net2.setInput(input);
    net2.run(&(FeedforwardPropagationRunner::Instance()));

    //Output
    cout<<"Test output: "<<net2.getOutput().at(0)<<endl;
    
    //Debug
    {
    //ostringstream ost;
    //net2.printDebugInfo(ost);
    //cout<<ost.str();
    }
    

    return 0;
}

