//MultilayerPerceptron.cpp

#include "MultilayerPerceptron.h"

using namespace std;

namespace pann
{
    namespace NetworkModel
    {
        Net* MultilayerPerceptron(vector<unsigned> layers, ActivationFunction::Base* af)
        {
            Net* net = new Net();
     
            if(layers.size() == 0)
                return net;

            vector< vector<Neuron*> > mlp(layers.size());

            //Input neurons
            for(unsigned i = 0; i < layers[0]; ++i)
            {
                Neuron* n = new Neuron(0);
                mlp[0].push_back(n);
                net->addInputNeuron(n);
            }

            if(layers.size() < 2)
                return net;

            //Layers
            //TODO: OpenGlHint
            for(unsigned l = 1; l < layers.size(); ++l)
                for(unsigned i = 0; i < layers[l]; ++i)
                {
                    ActivationFunction::Base *af;

                    if(l == layers.size() - 1) //Last layer is Linear
                        af = ActivationFunction::Linear::Instance();
                    else
                        af = ActivationFunction::TanH::Instance();

                    Neuron* n = new Neuron(af);
                    mlp[l].push_back(n);

                    //Add bias
                    n->bias = new Weight(1);
                }
       
            //Connections
            for(unsigned i = 0; i < mlp.size() - 1; i++) //layers
                for(unsigned j = 0; j < mlp[i].size(); j++) //prev layer
                    for(unsigned k = 0; k < mlp[i+1].size(); k++) //next layer
                        //Connection from current layer (i) to next (i+1)
                        net->addConnection(mlp[i][j], mlp[i+1][k]);
            
            return net;
        };
    };

}; //pann

