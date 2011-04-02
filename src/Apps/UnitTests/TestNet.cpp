//TestNet.cpp

#include <boost/progress.hpp>
#include <boost/assign/std.hpp>

#include "pann-shit.h"

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
            tnet->add_input_neuron(n1);
            tnet->add_connection(n1, n2);
            tnet->add_connection(n2, n3);
            cout<<"Constructed Net"<<endl;
        }
        cout<<"Layers: "<<tnet->get_cache().layers.size()<<endl;

        // N1 -X-> N2 -X-> N3
        tnet->remove_neuron(tnet->get_cache().layers[0][0]);
        //tnet.delConnection(tnet.get_cache().layers[1][0], tnet.get_cache().layers[2][0]);
        cout<<"Neuron deleted"<<endl;
        //But NetCache still stores ptr to it. Let's regenerate it manually
        tnet->get_cache();
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

        tnet->add_input_neuron(ni);
        tnet->add_connection(ni, n1);
        tnet->add_connection(ni, n2);
        tnet->add_connection(ni, n3);
        tnet->add_connection(n1, no);
        tnet->add_connection(n2, no);
        tnet->add_connection(n3, no);

        tnet->add_connection(n1, n2); //same level recursion
        tnet->add_connection(n1, n3);
        tnet->add_connection(n2, n1);
        tnet->add_connection(n2, n3);
        tnet->add_connection(n3, n1);
        tnet->add_connection(n3, n2);

        tnet->add_connection(n3, n3); //sel-recurrent
        tnet->add_connection(no, n2); //recurrent
        tnet->add_connection(no, ni); //from output to input recursion

        const NetCache& cache = tnet->get_cache();
        for(unsigned i = 0; i < cache.layers.size(); ++i)
            cout<<cache.layers[i].size()<<endl;


        {
            Storage::save<Storage::xml_out>(tnet, "test_ser_net.xml");
            NetPtr xml;
            Storage::load<Storage::xml_in>(xml, "test_ser_net.xml");
            const NetCache& cache = xml->get_cache();
            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
        }
        {
            Storage::save<Storage::txt_out>(tnet, "test_ser_net.txt");
            NetPtr txt;
            Storage::load<Storage::txt_in>(txt, "test_ser_net.txt");
            const NetCache& cache = txt->get_cache();
            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
        }
        {
            Storage::save<Storage::bin_out>(tnet, "test_ser_net.bin");
            NetPtr bin;
            Storage::load<Storage::bin_in>(bin, "test_ser_net.bin");
            const NetCache& cache = bin->get_cache();
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
            vector<tuple<unsigned, TfPtr> > layers;
            layers.push_back(make_tuple(1, Linear::Instance()));
            for(unsigned i = 0; i < layers_count; ++i)
                layers.push_back(make_tuple(9, TanH::Instance()));
            layers.push_back(make_tuple(1, Linear::Instance()));

            NetPtr net_ptr = MultilayerPerceptron(layers);
            /*
            net_ptr->run(RandomizeWeightsGaussRunner::Instance());

            const NetCache& cache = net_ptr->get_cache();

            for(unsigned i = 0; i < cache.layers.size(); ++i)
                cout<<cache.layers[i].size()<<endl;
            cout<<"MLP ready\n";
            */

            /*
            //Show all weights
            {
                const NetCache& cache = net->get_cache();
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
                        net_ptr->set_input(tp.input());
                        net_ptr->run(FeedforwardPropagationRunner::Instance());
                    }
                }
                cout<<"Total: ";
            }
            //Output
            valarray<Float> output;
            net_ptr->get_output(output);
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
            net2->get_output(output);
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

