//MultilayerPerceptron.cpp

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"

#include "MultilayerPerceptron.h"

using std::vector;
using boost::tuple;
using boost::shared_ptr;

namespace pann
{
    Net&
    MultilayerPerceptron(vector<tuple<unsigned, ActivationFunction::Base*> > _layers)
    {
        Net* net = new Net();
 
        if(_layers.size() == 0)
            return *net;

        vector< vector<shared_ptr<Neuron> > > mlp(_layers.size());

        //Layers
        //TODO: OpenGlHint
        for(unsigned l = 0; l < _layers.size(); ++l)
        {
            ActivationFunction::Base* af = _layers[l].get<1>();
            if(!af)
                af = ActivationFunction::TanH::Instance();

            for(unsigned i = 0; i < _layers[l].get<0>(); ++i)
            {
                //Neuron with bias
                shared_ptr<Neuron> n(new Neuron(af, shared_ptr<Weight>(new Weight(1)))); 
                mlp[l].push_back(n);
                if(l == 0)
                    net->addInputNeuron(n);
            }
        }
   
        //Connections
        for(unsigned i = 0; i < mlp.size() - 1; i++) //layers
            for(unsigned j = 0; j < mlp[i].size(); j++) //prev layer
                for(unsigned k = 0; k < mlp[i+1].size(); k++) //next layer
                    //Connection from current layer (i) to next (i+1)
                    net->addConnection(mlp[i][j], mlp[i+1][k], shared_ptr<Weight>(new Weight(1)));
        
        return *net;
    };

}; //pann

