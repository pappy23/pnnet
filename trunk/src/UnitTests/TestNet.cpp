//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "Type.h"
#include "Net.h"
#include "Storage.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    //Input
    vector<Float> input;
    input.push_back(3);

    {
        //MLP simulation
        const unsigned layers_count = 10;
        const unsigned neurons_count = 1000;
        const unsigned runs_count = 5;
        const unsigned thread_count = 4; 
        ActivationFunction::Base* af = ActivationFunction::TanH::Instance();

        Net net(thread_count);
        vector< vector<unsigned> > layers(layers_count);
        
        layers[0].push_back(net.addInputNeuron());

        unsigned owner = 1;
        for(unsigned i = 1; i < layers_count - 1; i++)
            for(unsigned j = 0; j < neurons_count; j++)
            {
                layers[i].push_back(net.addNeuron(af));
                net.setNeuronOwner(layers[i][j], owner);
                if(++owner > 64)
                    owner = 1;
            }
        
        layers[layers_count - 1].push_back(net.addOutputNeuron(af));

        cout<<"Neurons constructed:\n";
        for(unsigned i = 0; i < layers.size(); i++)
            cout<<layers[i].size()<<" ";
        cout<<endl;
        
        //Connect layers
        for(unsigned i = 0; i < layers_count - 1; i++) //layers
            for(unsigned j = 0; j < layers[i].size(); j++) //prev layer
                for(unsigned k = 0; k < layers[i+1].size(); k++) //next layer
                    net.addConnection(layers[i][j], layers[i+1][k], 1);

        cout<<"MLP ready\n";

        //Test run()
        {
            progress_timer t;
            for(unsigned i = 0; i < runs_count; i++)
            {
                cout<<i+1<<"-th run: "; 
                cout.flush();
                {
                    progress_timer t;
                    net.setInput(input);
                    net.run(FeedforwardPropagationRunner::Instance());
                }
            }
            cout<<"Total: ";
            //Output
            cout<<"Test output: "<<setprecision(5)<<fixed<<net.getOutput().at(0)<<endl;
        }
        
        //Serialization test
        Storage::save(net, "test_net.txt");

        //Memory consumption test
        cout<<"It's time to do memory test\n";
        sleep(20);

        for(unsigned i = 0; i < layers.size(); i++)
            cout<<layers[i].size()<<" ";
        cout<<endl;
    }

    Net net2;
    cout<<"New net...OK\n";
    Storage::load(net2, "test_net.txt");

    //Test run()
    net2.setInput(input);
    net2.run(FeedforwardPropagationRunner::Instance());

    //Output
    cout<<"Test output: "<<setprecision(5)<<net2.getOutput().at(0)<<endl;
    
    //Debug
    {
    //ostringstream ost;
    //net2.printDebugInfo(ost);
    //cout<<ost.str();
    }
    

    return 0;
}

