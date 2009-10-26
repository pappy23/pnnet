//MultilayerPerceptron.cpp

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"

#include "MultilayerPerceptron.h"

using std::vector;
using boost::tuple;

namespace pann
{
    NetPtr
    MultilayerPerceptron(vector<tuple<unsigned, ActivationFunction::Base*> > _layers)
    {
        NetPtr net(new Net());

        if(_layers.size() == 0)
            return net;

        vector<vector<NeuronPtr> > mlp(_layers.size());

        //Layers
        //TODO: OpenGlHint
        for(unsigned l = 0; l < _layers.size(); ++l)
        {
            ActivationFunction::Base* af = _layers[l].get<1>();
            if(!af)
                af = ActivationFunction::TanH::Instance();

            for(unsigned i = 0; i < _layers[l].get<0>(); ++i)
            {
                NeuronPtr n;
                if(l == 0)
                {
                    n.reset(new Neuron(af));
                    net->addInputNeuron(n);
                } else {
                    n.reset(new Neuron(af, WeightPtr(new Weight(1))));
                }

                mlp[l].push_back(n);
            }
        }

        //Connections
        for(unsigned i = 0; i < mlp.size() - 1; i++) //layers
            for(unsigned j = 0; j < mlp[i].size(); j++) //prev layer
                for(unsigned k = 0; k < mlp[i+1].size(); k++) //next layer
                    //Connection from current layer (i) to next (i+1)
                    net->addConnection(mlp[i][j], mlp[i+1][k]);

        return net;
    };

}; //pann
