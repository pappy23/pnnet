//Neuron.cpp

#include "Neuron.h"

using namespace std;

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base* _activationFunction) throw()
    {
        activationFunction = _activationFunction;
        ownerThread = 0;
        receptiveField = 0;
        activationValue = _activationFunction->f(0);
    } //Neuron

    Neuron::~Neuron() throw()
    {
    } //~Neuron

    void
    Neuron::setOwnerThread(unsigned _thread) throw(E<Exception::RangeMismatch>)
    {
        if(0 > _thread || _thread > 100)
            throw E<Exception::RangeMismatch>()<<"Neuron::setOwnerThread(): thread must be between 0 and 100\n";

        ownerThread =_thread;
    } //setOwnerThread

    unsigned
    Neuron::getOwnerThread() const throw()
    {
        return ownerThread;
    } //getOwnerThread

    const ActivationFunction::Base*
    Neuron::getActivationFunction() const throw()
    {
        return activationFunction;
    } //getOwnerThread

    list<Link>::iterator
    Neuron::findLink(Neuron* _to, Link::Direction _direction) throw(E<Exception::MultipleOccurance>, E<Exception::ObjectNotFound>)
    {                                                                                
        list<Link>::iterator result = links.end();
        list<Link>::iterator iter = links.begin();
        for(; iter != links.end(); ++iter)                                           
        {                                                                            
            if(iter->getTo() == _to && iter->getDirection() == _direction)                     
            {                                                                        
                if(result != links.end()) //Multiple parallel links exist          
                    throw E<Exception::MultipleOccurance>()<<"findLink(): detected parallel links\n";
                else                                                                              
                    result = iter;                                                                
            }                                                                                     
        }                                                                                         

        if(result == links.end())
            throw E<Exception::ObjectNotFound>()<<"findLink(): can't find required link\n";

        return result;
    } //findLink

}; //pann
