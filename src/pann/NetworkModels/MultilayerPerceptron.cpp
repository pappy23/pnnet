//MultilayerPerceptron.cpp

#include "Core/Net.h"
#include "Core/Neuron.h"
#include "Core/Weight.h"

#include "MultilayerPerceptron.h"

using namespace std;

namespace pann
{
    namespace NetworkModel
    {
        Net&
        MultilayerPerceptron(vector<unsigned> _layers, ActivationFunction::Base* _af)
        {
            Net* net = new Net();
     
            if(_layers.size() == 0)
                return *net;

            vector< vector<shared_ptr<Neuron> > > mlp(_layers.size());

            //Input neurons
            for(unsigned i = 0; i < _layers[0]; ++i)
            {
                shared_ptr<Neuron> n(new Neuron(0));
                mlp[0].push_back(n);
                net->addInputNeuron(n);
            }

            if(_layers.size() < 2)
                return *net;

            //Layers
            //TODO: OpenGlHint
            for(unsigned l = 1; l < _layers.size(); ++l)
                for(unsigned i = 0; i < _layers[l]; ++i)
                {
                    ActivationFunction::Base *af;

                    if(l == _layers.size() - 1) //Last layer is Linear
                        af = ActivationFunction::Linear::Instance();
                    else
                        af = _af;

                    mlp[l].push_back(
                            shared_ptr<Neuron>(new Neuron(
                                    af, 
                                    shared_ptr<Weight>(new Weight(1))
                            ))
                    ); //Neuron with bias
                }
       
            //Connections
            for(unsigned i = 0; i < mlp.size() - 1; i++) //layers
                for(unsigned j = 0; j < mlp[i].size(); j++) //prev layer
                    for(unsigned k = 0; k < mlp[i+1].size(); k++) //next layer
                        //Connection from current layer (i) to next (i+1)
                        net->addConnection(mlp[i][j], mlp[i+1][k], shared_ptr<Weight>(new Weight(1)));
            
            return *net;
        };
    };

}; //pann

