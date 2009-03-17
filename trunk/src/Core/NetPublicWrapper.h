#ifndef NETPUBLICWRAPPER_H
#define NETPUBLICWRAPPER_H

#include "Net.h"

namespace pann
{
    class NetPublicWrapper
    {
    public:
        Net* net;

    public:
        NetPublicWrapper(Net* _net);
        ~NetPublicWrapper();

        const NetCache& getCache();
        const std::map<unsigned, Neuron>& getNeurons();
        const std::map<unsigned, Weight>& getWeights();
    };

}; //pann

#endif
