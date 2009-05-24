//TestNet.cpp

#include <iostream>
#include <iomanip>

#include <boost/progress.hpp>

#include "pann.h"

using namespace std;
using namespace pann;
using namespace pann::ActivationFunction;
using namespace boost;

int main()
{
    Net tnet;
    // N1 ---> N2 ---> N3
    {
        shared_ptr<Neuron> n1(new Neuron(ActivationFunction::Linear::Instance()));
        shared_ptr<Neuron> n2(new Neuron(ActivationFunction::Linear::Instance()));
        shared_ptr<Neuron> n3(new Neuron(ActivationFunction::Linear::Instance()));
        tnet.addInputNeuron(n1);
        tnet.addConnection(n1, n2);
        tnet.addConnection(n2, n3);
        cout<<"Constructed Net"<<endl;
    }
    cout<<"Layers: "<<tnet.getCache().layers.size()<<endl;

    // N1 -X-> N2 -X-> N3
    tnet.removeNeuron(tnet.getCache().layers[0][0]);
    //tnet.delConnection(tnet.getCache().layers[1][0], tnet.getCache().layers[2][0]);
    cout<<"Neuron deleted"<<endl;
    //But NetCache still stores ptr to it. Let's regenerate it manually
    tnet.getCache();
    cout<<"Cache regenerated"<<endl;

    // N1 -X-> ?  -X-> N3
    cout<<"That's all, folks!"<<endl;
/*

    const unsigned runs_count = 3;
    const unsigned layers_count = 0;

    TrainPattern tp(1, 1);
    tp.input[0] = -100;

    {
        vector<tuple<unsigned, Base*> > layers;
        layers.push_back(make_tuple(1, Linear::Instance()));
        for(unsigned i = 0; i < layers_count; ++i)
            layers.push_back(make_tuple(9, TanH::Instance()));
        layers.push_back(make_tuple(1, Linear::Instance()));

        Net& net = MultilayerPerceptron(layers);

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
*/
    return 0;
}

