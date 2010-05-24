
#include "pann-shit.h"
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace pann;

int main(int argc, char ** argv)
{
    vector<unsigned> layers;
    layers += 1,2;
    NetPtr net = make_convnet(layers, 1.0, 2, 2, 1, 1, Linear::Instance(), TanH::Instance(), TanH::Instance(), TanH::Instance());

    net->run(FeedforwardPropagationRunner::Instance());

    const NetCache & cache = net->get_cache();
    cout<<"Cache layers["<<cache.layers.size()<<"] : ";
    for(unsigned i = 0; i < cache.layers.size(); ++i)
        cout<<cache.layers[i].size()<<" ";
    cout<<endl;

    /*
    cout<<"Tracing:\n";
    for(unsigned layer_no = 0; layer_no < cache.layers.size(); ++layer_no)
    {
        cout<<"Layer "<<layer_no<<'\n';
        for(unsigned neuron_no = 0; neuron_no < cache.layers[layer_no].size(); ++neuron_no)
        {
            NeuronPtr n = cache.layers[layer_no][neuron_no];
            cout<<"uid:\t"<<n->get_attr(pann::hash("uid"))<<"\nlayer:\t"<<n->get_attr((pann::hash("layer")))<<
                    "\nplane:\t"<<n->get_attr(pann::hash("plane"))<<"\nx:\t"<<n->get_attr(pann::hash("x"))<<
                    "\ny:\t"<<n->get_attr(pann::hash("y"))<<"\n";
            BOOST_FOREACH( const Link & link, n->input_links )
                    cout<<"-> "<<link.get_to()->get_attr(pann::hash("uid"))<<", w = "<<link.get_weight()->get_attr(pann::hash("uid"))<<'\n';
            cout<<endl;
        };
    };
    */

    return 0;
}; //main

