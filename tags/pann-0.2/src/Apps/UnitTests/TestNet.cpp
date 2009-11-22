//TestNet.cpp

#include "pann.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;
using namespace pann::ConvolutionalNetworkTypes;

int main()
{
    {
        cout<<"TESTING NET CONSTRUCTION\n";
        NetPtr tnet(new Net());
        // N1 ---> N2 ---> N3
        {
            NeuronPtr n1(NeuronFactory::PyramidalNeuron(Linear::Instance()));
            NeuronPtr n2(NeuronFactory::PyramidalNeuron(Linear::Instance()));
            NeuronPtr n3(NeuronFactory::PyramidalNeuron(Linear::Instance()));
            tnet->addInputNeuron(n1);
            tnet->addConnection(n1, n2);
            tnet->addConnection(n2, n3);
            cout<<"Constructed Net"<<endl;
        }
        cout<<"Layers: "<<tnet->getCache().layers.size()<<endl;

        // N1 -X-> N2 -X-> N3
        tnet->removeNeuron(tnet->getCache().layers[0][0]);
        //tnet.delConnection(tnet.getCache().layers[1][0], tnet.getCache().layers[2][0]);
        cout<<"Neuron deleted"<<endl;
        //But NetCache still stores ptr to it. Let's regenerate it manually
        tnet->getCache();
        cout<<"Cache regenerated"<<endl;

        // N1 -X-> ?  -X-> N3
        cout<<"That's all, folks!"<<endl;
    }

    {
        cout<<"TESTING CACHE GENERATION\n";
        NetPtr tnet(new Net());
        //Hopfield model
        //ACHTUNG!! Chinese code follows :)
        NeuronPtr ni(NeuronFactory::PyramidalNeuron(Linear::Instance()));
        NeuronPtr n1(NeuronFactory::PyramidalNeuron(Linear::Instance()));
        NeuronPtr n2(NeuronFactory::PyramidalNeuron(Linear::Instance()));
        NeuronPtr n3(NeuronFactory::PyramidalNeuron(Linear::Instance()));
        NeuronPtr no(NeuronFactory::PyramidalNeuron(Linear::Instance()));

        tnet->addInputNeuron(ni);
        tnet->addConnection(ni, n1);
        tnet->addConnection(ni, n2);
        tnet->addConnection(ni, n3);
        tnet->addConnection(n1, no);
        tnet->addConnection(n2, no);
        tnet->addConnection(n3, no);

        tnet->addConnection(n1, n2); //same level recursion
        tnet->addConnection(n1, n3);
        tnet->addConnection(n2, n1);
        tnet->addConnection(n2, n3);
        tnet->addConnection(n3, n1);
        tnet->addConnection(n3, n2);

        tnet->addConnection(n3, n3); //sel-recurrent
        tnet->addConnection(no, n2); //recurrent
        tnet->addConnection(no, ni); //from output to input recursion

        const NetCache& cache = tnet->getCache();
        for(unsigned i = 0; i < cache.layers.size(); ++i)
            cout<<cache.layers[i].size()<<endl;


        {
            Storage::save<Storage::xml_out>(tnet, "test_ser_net.xml");
            NetPtr xml;
            Storage::load<Storage::xml_in>(xml, "test_ser_net.xml");
            const NetCache& cache = xml->getCache();
            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
        }
        {
            Storage::save<Storage::txt_out>(tnet, "test_ser_net.txt");
            NetPtr txt;
            Storage::load<Storage::txt_in>(txt, "test_ser_net.txt");
            const NetCache& cache = txt->getCache();
            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
        }
        {
            Storage::save<Storage::bin_out>(tnet, "test_ser_net.bin");
            NetPtr bin;
            Storage::load<Storage::bin_in>(bin, "test_ser_net.bin");
            const NetCache& cache = bin->getCache();
            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
        }
    }

    {
        cout<<"TESTING MULTILAYER PERCEPTRON CREATION AND LEARNING\n";
        const unsigned runs_count = 3;
        const unsigned layers_count = 1;

        TrainPattern tp(1, 1);
        tp.input()[0] = -10;

        {
            vector<tuple<unsigned, ActivationFunctionPtr> > layers;
            layers.push_back(make_tuple(1, Linear::Instance()));
            for(unsigned i = 0; i < layers_count; ++i)
                layers.push_back(make_tuple(9, TanH::Instance()));
            layers.push_back(make_tuple(1, Linear::Instance()));

            NetPtr net_ptr = MultilayerPerceptron(layers);
            /*
            net_ptr->run(RandomizeWeightsGaussRunner::Instance());

            const NetCache& cache = net_ptr->getCache();

            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
            cout<<"MLP ready\n";
            */

            /*
            //Show all weights
            {
                const NetCache& cache = net->getCache();
                for(unsigned layer = 0; layer < cache.layers.size(); ++layer)
                {
                    for(unsigned i = 0; i < cache.layers[layer].size(); ++i)
                    {
                        cout<<"N"<<i<<": ";
                        WeightPtr w = cache.layers[layer][i]->getBias();
                        if(w)
                            cout<<w->getValue()<<"b ";
                        list<Link> & links_in = cache.layers[layer][i]->getInConnections();
                        for(list<Link>::iterator it = links_in.begin(); it != links_in.end(); ++it)
                            cout<<it->getWeight()->getValue()<<" ";
                        cout<<"\t";
                    }
                    cout<<endl;
                }
            }
            */

            //Test run()
            {
                progress_timer t;
                for(unsigned i = 0; i < runs_count; i++)
                {
                    cout<<i+1<<"-th run: "; 
                    cout.flush();
                    {
                        progress_timer t;
                        net_ptr->setInput(tp.input());
                        net_ptr->run(FeedforwardPropagationRunner::Instance());
                    }
                }
                cout<<"Total: ";
            }
            //Output
            valarray<Float> output;
            net_ptr->getOutput(output);
            cout<<"Test output: "<<setprecision(5)<<fixed<<output[0]<<endl;

            //Serialization test
            Storage::save<Storage::xml_out>(net_ptr, "test_net.xml");

            //Memory consumption test
            cout<<"It's time to do memory test\n";
    //        sleep(5);
        }

        NetPtr net2(new Net());
        cout<<"New net...OK\n";
        Storage::load<Storage::xml_in>(net2, "test_net.xml");
        cout<<"Loading done\n";

        //Test run()
        {
            progress_timer t;
            //net2->setInput(tp.input);
            net2->run(FeedforwardPropagationRunner::Instance());
            //Output
            valarray<Float> output;
            net2->getOutput(output);
            //cout<<"Test output: "<<setprecision(5)<<fixed<<output[0]<<endl;
        }
    }

    {
        cout<<"TESTING CONVOLUTIONAL NETWORK CONSTRUCTION\n";

        vector<unsigned> planes;
        planes += 2,2,2;

        Model model = ConvolutionalNetworkModel(planes, 0.8, 5, 5, 3, 3);

        //Debug
        for(unsigned i = 0; i < model.size(); ++i)
        {
            Debug()<<"Planes: "<<model[i].size()<<": ";
            for(unsigned j = 0; j < model[i].size(); ++j)
                Debug()<<model[i][j].size()<<"x"<<model[i][j][0].size()<<" ";
            Debug()<<"\n";
        }

        NetPtr net = ConvolutionalNetwork(planes);
        Storage::save<Storage::txt_out>(net, "test_conv.net");
    }

    return 0;
}
