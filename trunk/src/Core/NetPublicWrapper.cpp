#include "NetPublicWrapper.h"

using namespace std;

namespace pann
{             
    NetPublicWrapper::NetPublicWrapper(Net* _net)
    {
        net = _net;
    }; //NetPublicWrapper

    NetPublicWrapper::~NetPublicWrapper()
    {
    }; //~NetPublicWrapper

    const NetCache&
    NetPublicWrapper::getCache()
    {
        if( !net->cache.isOk() )
            net->regenerateCache();

        return net->cache;
    }; //getCache

    const map<unsigned, Neuron>&
    NetPublicWrapper::getNeurons()
    {
        return net->neurons;
    }; //getNeurons

    const map<unsigned, Weight>&
    NetPublicWrapper::getWeights()
    {
        return net->weights;
    }; //getNeurons

}; //namespace pann

