//Neuron.cpp

#include "Neuron.h"

using namespace std;

namespace pann
{
    Neuron::Neuron() :
            activationFunction(ActivationFunction::Linear::Instance()),
            ownerThread(0),
            receptiveField(0),
            activationValue(activationFunction->f(0)),
            oglHint(0)
    {
    } //Neuron

    Neuron::Neuron(ActivationFunction::Base* _activationFunction) :
            activationFunction(_activationFunction),
            ownerThread(0),
            receptiveField(0),
            activationValue(_activationFunction->f(0)),
            oglHint(0)
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    void
    Neuron::setOwnerThread(unsigned _thread)
    {
        if(0 > _thread || _thread > 100)
            throw Exception::RangeMismatch()<<"Neuron::setOwnerThread(): thread must be between 0 and 100\n";

        ownerThread =_thread;
    } //setOwnerThread

    unsigned
    Neuron::getOwnerThread() const
    {
        return ownerThread;
    } //getOwnerThread

    const ActivationFunction::Base*
    Neuron::getActivationFunction() const
    {
        return activationFunction;
    } //getOwnerThread

    list<Link>::iterator
    Neuron::findLink(NeuronIter _to, Link::Direction _direction)
    {                                                                                
        list<Link>::iterator iter = links.begin(),                                   
        result = links.end();                                   
        for(; iter != links.end(); ++iter)                                           
        {                                                                            
            if(iter->getToIter() == _to && iter->getDirection() == _direction)                     
            {                                                                        
                if( result != links.end() ) //Multiple parallel links exist          
                    throw Exception::MultipleOccurance()<<"findLink(): detected parallel links\n";
                else                                                                              
                    result = iter;                                                                
            }                                                                                     
        }                                                                                         

        if( result == links.end() )
            throw Exception::ObjectNotFound()<<"findLink(): can't find required link\n";

        return result;
    } //findLink

}; //pann
