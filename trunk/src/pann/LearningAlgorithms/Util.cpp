//Util.cpp

#include "Util.h"

#include "Core/Net.h"
#include "Core/NetCache.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Random.h"
#include "Core/Weight.h"

using namespace std;

namespace pann
{             
    namespace Util
    {
        void
        randomizeWeightsGauss(Net& _net, Float _min, Float _max) throw()
        {
            const NetCache& cache = _net.getCache();

            for(unsigned layer = 0; layer < cache.layers.size(); ++layer)
                for(unsigned n = 0; n < cache.layers[layer].size(); ++n)
                {
                    //Tune bias values
                    if(cache.layers[layer][n]->hasBias())
                        cache.layers[layer][n]->getBias()[Weight::value] = rand(_min, _max);

                    //Link weights
                    std::list<Link>::const_iterator l_iter = cache.layers[layer][n]->links.begin();
                    for(; l_iter != cache.layers[layer][n]->links.end(); ++l_iter)
                        if(l_iter->getDirection() == Link::in)
                            const_cast<Link&>(*l_iter).getWeight()[Weight::value] = rand(_min, _max);
                }
        } //randomizeWeightsGauss

        void randomizeWeightsAccordingToInputsCount(Net& _net, Float _min, Float _max) throw()
        {
            const NetCache& cache = _net.getCache();

            for(unsigned layer = 0; layer < cache.layers.size(); ++layer)
                for(unsigned n = 0; n < cache.layers[layer].size(); ++n)
                {
                    Float C = sqrt(Float(cache.layers[layer][n]->links.size() / 2.0));
                    if(C == 0) C = 10.0;

                    //Tune bias values
                    if(cache.layers[layer][n]->hasBias())
                        cache.layers[layer][n]->getBias()[Weight::value] = rand(_min, _max) / C;

                    //Link weights
                    std::list<Link>::const_iterator l_iter = cache.layers[layer][n]->links.begin();
                    for(; l_iter != cache.layers[layer][n]->links.end(); ++l_iter)
                        if(l_iter->getDirection() == Link::in)
                            const_cast<Link&>(*l_iter).getWeight()[Weight::value] = rand(_min, _max) / C;
                }
        } //randomizeWeightsAccordingToInputsCount

    }; //Util
}; //pann

