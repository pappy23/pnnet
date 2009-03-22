//Neuron.h

#ifndef NEURON_H
#define NEURON_H

#include "Includes.h"
#include "Object.h"
#include "ActivationFunction.h"
#include "Link.h"
#include "OpenGLHint.h"
#include "LearningHint.h"

namespace pann
{
    class Neuron : public Object
    {
        /* Private attributes */
    private:
        ActivationFunction::Base* activationFunction;

        /**
         * Thread with this number will take care of our Neuron
         */
        unsigned ownerThread;

        /* Public attributes
         * Note: Neuron is usually hidden by Net,
         * so there is nothing to worry about
         */
    public:
        Float receptiveField;
        Float activationValue;
        std::list<Link> links; //!< List of Link, both directions
        OpenGLHint* oglHint;
        LearningHint::Base* learningHint;
    
        /* Public interface */
    public:
        Neuron();
        Neuron(ActivationFunction::Base*);
        ~Neuron();

        void setOwnerThread(unsigned _thread);
        unsigned getOwnerThread() const;

        const ActivationFunction::Base* getActivationFunction() const;

        /**
         * Helper. Finds and returns iterator to list<> links for NeuronIter _to
         */
        std::list<Link>::iterator findLink(NeuronIter _to, Link::Direction _direction);

        /* Debug */
    public:
        virtual void printDebugInfo(std::ostringstream& ost) const
        {
            ost<<" Neuron\n";
            ost<<"  ownerThread: "<<ownerThread<<std::endl;
            ost<<"  activationFunction: "<<activationFunction->getId()<<std::endl;
            std::list<Link>::const_iterator it = links.begin();
            for(; it != links.end(); ++it)
            {
                it->printDebugInfo(ost);
                ost<<"    to: "<<it->getToIter()->first<<std::endl;
            }
        };

        /* Serialization */
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

                bool isHintAvailable;
                
                //OpenGL hint
                (oglHint != 0) ? (isHintAvailable = true) : (isHintAvailable = false);
                ar & isHintAvailable;                    
                if(isHintAvailable)
                    ar & (*oglHint);
                
                //Learning hint
                (learningHint != 0) ? (isHintAvailable = true) : (isHintAvailable = false);
                ar & isHintAvailable;                    
                if(isHintAvailable)
                {
                    LearningHint::HintId lhintId = learningHint->getTypeId();
                    ar & lhintId;
                    ar & (*learningHint);
                }
                
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

                bool isHintAvailable;

                //OpenGL hint
                ar & isHintAvailable;
                if(isHintAvailable)
                {
                    oglHint = new OpenGLHint;
                    ar & oglHint;
                }

                //Learning hint
                ar & isHintAvailable;
                if(isHintAvailable)
                {
                    LearningHint::HintId lhintId;
                    ar & lhintId;
                    learningHint = LearningHint::getById(lhintId);
                    ar & learningHint;
                }
            };

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

}; //pann

#endif //NEURON_H

