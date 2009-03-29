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

            vector< vector<unsigned> > mlp(layers.size());

            //Input neurons
            for(unsigned i = 0; i < layers[0]; ++i)
                mlp[0].push_back(net->addInputNeuron());

            if(layers.size() < 2)
                return net;

            //Layers
            //TODO: OpenGlHint
            for(unsigned l = 1; l < layers.size(); ++l)
                for(unsigned i = 0; i < layers[l]; ++i)
                {
                    mlp[l].push_back(net->addNeuron(af));

                    //Add bias connection
                    net->addConnection(net->getBiasId(), mlp[l][i], 1);
                }
       
            //Connections
            for(unsigned i = 0; i < mlp.size() - 1; i++) //layers
                for(unsigned j = 0; j < mlp[i].size(); j++) //prev layer
                    for(unsigned k = 0; k < mlp[i+1].size(); k++) //next layer
                        //Connection from current layer (i) to next (i+1)
                        net->addConnection(mlp[i][j], mlp[i+1][k], 1);
            
            return net;
        };
    };

}; //pann

