//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"

namespace pann
{
    class Neuron : public Object
    {
    private:
        boost::shared_ptr<ActivationFunction::Base> activationFunction;
        int ownerThread; //Thread with this number will take care of our Neuron

    public:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
    
    public:
        Neuron();
        Neuron(boost::shared_ptr<ActivationFunction::Base>);
        ~Neuron();

        void connect(NeuronIter _to, Link::Direction _direction, Float _weightValue);
        void connect(NeuronIter _to, Link::Direction _direction, boost::shared_ptr<Weight> _weight);
        void disconnect(NeuronIter _to, Link::Direction _direction);

        void setOwnerThread(int _thread);
        int getOwnerThread();

        const boost::shared_ptr<ActivationFunction::Base>& getActivationFunction();

    private:
        //Helper. Finds and returns iterator to list<> links for Neuron& _to
        std::list<Link>::iterator findLink(NeuronIter _to, Link::Direction _direction);

    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<" Neuron\n";
            ost<<"  ownerThread: "<<ownerThread<<std::endl;
            std::list<Link>::iterator it = links.begin();
            for(; it != links.end(); ++it)
                it->printDebugInfo(ost);
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);
                ar & activationFunction;
                ar & ownerThread;
                ar & receptiveField;
                ar & activationValue;
                ar & links;
            };
    };

}; //pann

#endif //NEURON_H

