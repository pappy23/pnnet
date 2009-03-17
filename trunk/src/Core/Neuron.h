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
        unsigned ownerThread; //Thread with this number will take care of our Neuron

    public:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
    
    public:
        Neuron();
        Neuron(ActivationFunction::Base*);
        ~Neuron();

        void setOwnerThread(unsigned _thread);
        unsigned getOwnerThread() const;

        const ActivationFunction::Base* getActivationFunction() const;

/*    private: */
        //Helper. Finds and returns iterator to list<> links for NeuronIter _to
        std::list<Link>::iterator findLink(NeuronIter _to, Link::Direction _direction);

    public:
        virtual void printDebugInfo(std::ostringstream& ost)
        {
            ost<<" Neuron\n";
            ost<<"  ownerThread: "<<ownerThread<<std::endl;
            ost<<"  activationFunction: "<<activationFunction->getId()<<std::endl;
            std::list<Link>::iterator it = links.begin();
            for(; it != links.end(); ++it)
            {
                it->printDebugInfo(ost);
                ost<<"    to: "<<it->getToIter()->first<<std::endl;
            }
        };

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void save(Archive & ar, const unsigned int version) const
            {
                ar & boost::serialization::base_object<Object>(*this);
                unsigned af_id = activationFunction->getId();
                ar & af_id;
                ar & ownerThread;
                ar & receptiveField;
                ar & activationValue;
                //ar & links; - Net responsibility
            };

        template<class Archive>
            void load(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Object>(*this);
                unsigned af_id;
                ar & af_id;
                activationFunction = ActivationFunction::getById(af_id);
                ar & ownerThread;
                ar & receptiveField;
                ar & activationValue;
                //ar & links; - Net responsibility
            };

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

}; //pann

#endif //NEURON_H

