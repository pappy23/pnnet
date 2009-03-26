//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace boost;

int main()
{
    const unsigned runs_count = 3;
    const unsigned layers_count = 2;
    const unsigned threads_count = 2;

    TrainPattern tp(1, 1);
    tp.input[0] = -100;

    {
        vector<unsigned> layers;
        layers.push_back(1);
        for(unsigned i = 0; i < layers_count; ++i)
            layers.push_back(2);
        layers.push_back(1);

        Net* net = NetworkModel::MultilayerPerceptron(layers, ActivationFunction::TanH::Instance());
        net->setThreadCount(threads_count);

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
                    net->setInput(tp.input);
                    net->run(FeedforwardPropagationRunner::Instance());
                }
            }
            cout<<"Total: ";
        }
        //Output
        valarray<Float> output;
        net->getOutput(output);
        cout<<"Test output: "<<setprecision(5)<<fixed<<output[0]<<endl;
        
        //Debug
        {
        ostringstream ost;
        //net->printDebugInfo(ost);
        cout<<ost.str();
        }
    
        //Serialization test
        Storage::save(*net, "test_net.xml");

        //Memory consumption test
        cout<<"It's time to do memory test\n";
//        sleep(5);
    }

    Net net2;
    cout<<"New net...OK\n";
    Storage::load(net2, "test_net.xml");

    //Debug
    {
    ostringstream ost;
    //net2.printDebugInfo(ost);
    cout<<ost.str();
    }
    
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

