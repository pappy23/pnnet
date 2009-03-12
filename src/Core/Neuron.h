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
        ActivationFunction::Base* activationFunction;
        int ownerThread; //Thread with this number will take care of our Neuron

    public:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
    
    public:
        Neuron();
        Neuron(ActivationFunction::Base*);
        ~Neuron();

        void connect(NeuronIter _to, Link::Direction _direction, Weight* _weight);
        void disconnect(NeuronIter _to, Link::Direction _direction);

        void setOwnerThread(int _thread);
        int getOwnerThread();

        ActivationFunction::Base* getActivationFunction();

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
                //ar & activationFunction; FIXME: can't serialize
                ar & ownerThread;
                ar & receptiveField;
                ar & activationValue;
                ar & links;
            };
    };

}; //pann

#endif //NEURON_H

