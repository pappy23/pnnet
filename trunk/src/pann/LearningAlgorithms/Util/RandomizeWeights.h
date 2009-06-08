#ifndef RANDOMIZEWEIGHTS_H
#define RANDOMIZEWEIGHTS_H

#include "Core/Type.h"
#include "Core/Runner.h"
#include "Core/Attributes.h"

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
    /**
     * Attributes used in neurons to draw network model
     * in pann_viewer
     */
    class WeightRandomizationAttributes : public Attributes
    {
    public:
        WeightRandomizationAttributes()
            : min(0), max(0)
        {
            groupName = hash("WeightRandomizationAttributes");
        };

        virtual ~WeightRandomizationAttributes() {};

        Float min;
        Float max;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<RandomizeWeightsAttributes, Attributes>(
                    static_cast<Attributes*>(NULL),
                    static_cast<RandomizeWeightsAttributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(min)
                & BOOST_SERIALIZATION_NVP(max);
            };

    }; //RandomizeWeightsAttributes
    ADD_PTR_TYPEDEF(RandomizeWeightsAttributes);

    /**
     * Assign initial weights from interval [_min; _max]
     * _min = -0.3, _max = +0.3 is good choise
     */
    class RandomizeWeightsGaussRunner : public Runner
    {
        RandomizeWeightsGaussRunner() {};

    public:
        static RunnerPtr Instance()
        {
            static RandomizeWeightsGaussRunner self;
            return RunnerPtr(&self);
        }

        virtual void run(NeuronPtr _neuron, NetPtr _net)
        {
            WeightRandomizationAttributes& attrs = _net.get<WeightRandomizationAttributes>();
            if(attrs.min == 0 && attrs.max == 0)
            {
                attrs.min = -0.3;
                attrs.max = +0.3;
            }

            //Tune bias values
            if(_neuron.getBias())
                _neuron.getBias()->setValue(rand(attrs.min, attrs.max));

            //Link weights
            BOOST_FOREACH(const Link& link, _neuron.getInConnections())
                link.getWeight()->setValue(rand(attrs.min, attrs.max));
        };

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

