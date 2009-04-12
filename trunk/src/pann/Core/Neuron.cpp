//Neuron.cpp

#include "Neuron.h"

using namespace std;

namespace pann
{
    const AttributeName Neuron::activationValue = hash("Neuron::activationValue", "Native");

    Neuron::Neuron(ActivationFunction::Base* _activationFunction) throw()
    {
        activationFunction = _activationFunction;
        bias = 0;
        
        if(activationFunction)
            (*this)[activationValue] = _activationFunction->f(0);
    } //Neuron

    Neuron::~Neuron() throw()
    {
    } //~Neuron

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
            if(&iter->getTo() == _to && iter->getDirection() == _direction)                     
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
