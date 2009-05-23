//TestNet.cpp

#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    const unsigned runs_count = 3;
    const unsigned layers_count = 0;

    TrainPattern tp(1, 1);
    tp.input[0] = -100;

    {
        vector<unsigned> layers;
        layers.push_back(1);
        for(unsigned i = 0; i < layers_count; ++i)
            layers.push_back(9);
        layers.push_back(1);

        Net& net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());

        cout<<"MLP ready\n";
        Storage::save<Storage::xml_out>(net, "test_net.xml");

        //Test run()
        {
            progress_timer t;
            for(unsigned i = 0; i < runs_count; i++)
            {
                cout<<i+1<<"-th run: "; 
                cout.flush();
                {
                    progress_timer t;
                    net.setInput(tp.input);
                    net.run(FeedforwardPropagationRunner::Instance());
                }
            }
            cout<<"Total: ";
        }
        //Output
        valarray<Float> output;
        net.getOutput(output);
        cout<<"Test output: "<<setprecision(5)<<fixed<<output[0]<<endl;
    
        //Serialization test
        Storage::save<Storage::xml_out>(net, "test_net.xml");

        //Memory consumption test
        cout<<"It's time to do memory test\n";
//        sleep(5);
    }

    Net net2;
    cout<<"New net...OK\n";
    Storage::load<Storage::xml_in>(net2, "test_net.xml");
    cout<<"Loading done\n";

    //Test run()
    {
        progress_timer t;
        net2.setInput(tp.input);
        net2.run(FeedforwardPropagationRunner::Instance());
        //Output
        valarray<Float> output;
        net2.getOutput(output);
        cout<<"Test output: "<<setprecision(5)<<fixed<<output[0]<<endl;
    }

    return 0;
}

