//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron 
    {
    protected:
        ActivationFunction& m_activation_function;
        std::vector<Neuron *> m_in_neurons;
		std::vector<float> m_input_weights;
		float m_lin_comb_output;
		float m_output;


    public:
        Neuron(ActivationFunction& activationFunction); 
        ~Neuron();
        
        //void connectTo(Neuron&, Link::Direction, float);
        //void connectTo(Neuron&, Weight*, Link::Direction);

        float activate();
    };

	class TraineeNeuron : public Neuron
	{
	protected:
		std::vector<Neuron *> m_out_neurons;

	};


	class TraineeNeuron1 : public TraineeNeuron
	{
	protected:
		int unicpole1;
		
	};

	class TraineeNeuron2 : public TraineeNeuron
	{
	protected:
		int unicpole1;
		
	};



}; //pann

#endif //NEURON_H

