//Util.cpp

#include <boost/random.hpp>

#include "Util.h"

#include "Net.h"
#include "NetCache.h"
#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

using namespace std;

namespace pann
{             
    namespace Util
    {
        valarray<Float>
        squash_copy(const valarray<Float> & _v, Float _min, Float _max) throw()
        {
            valarray<Float> result = _v;
            squash(result, _min, _max);

            return _v;
        } //squash_copy

        void
        squash(valarray<Float> & _v, Float _min, Float _max) throw()
        {
            if(_min > _max)
                swap(_min, _max);

            Float min = _v.min();
            Float max = _v.max();

            if(max == min) //very strange
            {
                _v = (Float) (_max + _min) / 2;
                return;
            }

            /*
             * To squah range [min; max] to new range [_min; _max] we use this formula:
             *
             * N = ( ( _max - _min ) / ( max - min ) ) * N +
             *      
             *      + ( _max - ( ( _max - _min ) / ( max - min ) ) * max )
             */
            Float a = ( _max - _min ) / ( max - min );
            Float b = _max - a * max;
            _v = a * _v + b;
        } //squash

        Float
        rand(Float _min, Float _max) throw()
        {
            static boost::lagged_fibonacci44497 engine;
            static boost::uniform_real<Float> distribution(0, 1);
            static boost::variate_generator<
                boost::lagged_fibonacci44497,
                boost::uniform_real<Float>
            > generator(engine, distribution);

            //Generate v from (0; 1) and squash it to (_min; _max) range
            Float v = generator();
            Float a = ( _max - _min );
            Float b = _max - a;
            v = a * v + b;

            return v;
        } //rand

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
