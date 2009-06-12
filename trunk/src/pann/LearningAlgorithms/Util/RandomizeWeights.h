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
        WeightRandomizationAttributes() : min(0), max(0) {};
        virtual ~WeightRandomizationAttributes() {};

        static const HashType getHash()
        {
            static HashType groupName = hash("WeightRandomizationAttributes");
            return groupName;
        };

    public:
        Float min;
        Float max;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                boost::serialization::void_cast_register<WeightRandomizationAttributes, Attributes>(
                    static_cast<WeightRandomizationAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_NVP(min)
                & BOOST_SERIALIZATION_NVP(max);
            };

    }; //RandomizeWeightsAttributes

    /**
     * Assign initial weights from interval [_min; _max]
     * _min = -0.3, _max = +0.3 is good choise
     */
    class RandomizeWeightsGaussRunner : public Runner
    {
        SINGLETON_SKELETON(RandomizeWeightsGaussRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    };
    REGISTER_SINGLETON_H(RandomizeWeightsGaussRunner);

    /**
     * Weight is random number from [_min/sqrt(C); _max/sqrt(C)]
     * C - number of inputs in current neuron
     * _min = -2.4, _max = +2.4 is good choise
     * See Gradien-Based Learning Applied to Document Recognition, Yann LeCun, app1, p.41
     * See S. Haykin, p252
     */
    class RandomizeWeightsAccordingToInputsCountRunner : public Runner
    {
        SINGLETON_SKELETON(RandomizeWeightsAccordingToInputsCountRunner, Runner);

        virtual void run(NeuronPtr _neuron, Net* _net) const;

        virtual RunDirection getDirection() const
        {
            return ForwardRun;
        }
    };
    REGISTER_SINGLETON_H(RandomizeWeightsAccordingToInputsCountRunner);

}; //pann

#endif

