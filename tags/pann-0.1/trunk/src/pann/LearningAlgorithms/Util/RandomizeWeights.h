#ifndef RANDOMIZEWEIGHTS_H
#define RANDOMIZEWEIGHTS_H

#include "Core/Type.h"
#include "Core/Runner.h"

/*
#include "Core/Net.h"
#include "Core/NetCache.h"
#include "Core/Neuron.h"
#include "Core/Link.h"
#include "Core/Random.h"
#include "Core/Weight.h"
*/

namespace pann
{
    namespace RandomizeWeightsAttributes
    {
        //Net
        const AttributeName min = hash("RandomizeWeightsAttributes::min", AlgorithmSpecificLearningParameters);
        const AttributeName max = hash("RandomizeWeightsAttributes::max", AlgorithmSpecificLearningParameters);
    }; //Attributes

    /**
     * Assign initial weights from interval [_min; _max]
     * _min = -0.3, _max = +0.3 is good choise
     */
    class RandomizeWeightsGaussRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        RandomizeWeightsGaussRunner() {};
        
    public:    
        ~RandomizeWeightsGaussRunner() {};

    public:
        static Runner& Instance()
        {
            if(!self)
                self = new RandomizeWeightsGaussRunner();

            return *self;
        }

        virtual void run(Neuron& _neuron, const Net& _net);
        
        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }
    };

    /**
     * Weight is random number from [_min/sqrt(C); _max/sqrt(C)]
     * C - number of inputs in current neuron
     * _min = -2.4, _max = +2.4 is good choise
     * See Gradien-Based Learning Applied to Document Recognition, Yann LeCun, app1, p.41
     * See S. Haykin, p252
     */
    class RandomizeWeightsAccordingToInputsCountRunner : public Runner
    {
    private:
        static Runner* self;

    private:
        RandomizeWeightsAccordingToInputsCountRunner() {};
        
    public:    
        ~RandomizeWeightsAccordingToInputsCountRunner() {};

    public:
        static Runner& Instance()
        {
            if(!self)
                self = new RandomizeWeightsAccordingToInputsCountRunner();

            return *self;
        }

        virtual void run(Neuron& _neuron, const Net& _net);
        
        virtual RunDirection getDirection()
        {
            return ForwardRun;
        }
    };

}; //pann

#endif

