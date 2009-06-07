#ifndef RANDOMIZEWEIGHTS_H
#define RANDOMIZEWEIGHTS_H

#include "Core/Type.h"
#include "Core/Runner.h"
#include "Core/Attributes.h"

namespace pann
{
    namespace AttributesGroup
    {
        const HashType WeightsRandomization = hash("RandomizeWeightsAttributes");
    }; //AttributesGroup

    ADD_PTR_TYPEDEF(WeightsRandomizationAttributes);

    class WeightsRandomizationAttributes : public Attributes
    {
    public:
        WeightsRandomizationAttributes() { };
        virtual ~WeightsRandomizationAttributes() { };

        virtual HashType getName() { return AttributesGroup::WeightsRandomization; };

        Float& min() { return m_min; };
        Float& max() { return m_max; };
        const Float& min() const { return m_min; };
        const Float& max() const { return m_max; };

    private:
        Float m_min;
        Float m_max;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                 boost::serialization::void_cast_register<WeightsRandomizationAttributes, Attributes>(
                    static_cast<WeightsRandomizationAttributes*>(NULL),
                    static_cast<Attributes*>(NULL));

                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Attributes)
                   & BOOST_SERIALIZATION_NVP(m_min)
                   & BOOST_SERIALIZATION_NVP(m_max);
            };
    }; //WeightsRandomizationAttributes

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

