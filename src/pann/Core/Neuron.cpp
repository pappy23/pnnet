//Neuron.cpp

#include "Weight.h"

#include "Neuron.h"

using namespace std;

namespace pann
{
    const AttributeName Neuron::activationValue = hash("Neuron::activationValue", NativeParameters);
    const AttributeName Neuron::receptiveField = hash("Neuron::receptiveField", NativeParameters);
    //const AttributeName Neuron::id = hash("Neuron::id", NativeParameters);

    Neuron::Neuron(ActivationFunction::Base* _activationFunction, Weight* _bias) throw()
    {
        activationFunction = _activationFunction;
        bias = _bias;
        
        if(activationFunction)
            fire();
        else
            (*this)[receptiveField] = (*this)[activationValue] = 0;
    } //Neuron

    Neuron::~Neuron() throw()
    {
    } //~Neuron

    bool
    Neuron::hasActivationFunction() const throw()
    {
        if(!activationFunction)
            return false;

        return true;
    } //hasActivationFunction

    const ActivationFunction::Base&
    Neuron::getActivationFunction() const throw(E<Exception::ObjectNotFound>)
    {
        if(!activationFunction)
            throw E<Exception::ObjectNotFound>()<<"Neuron::getActivationFunction(): No activation function!\n";

        return *activationFunction;
    } //getOwnerThread

    bool
    Neuron::hasBias() const throw()
    {
        if(bias)
            return true;

        return false;
    } //hasBias

    Weight&
    Neuron::getBias() throw(E<Exception::ObjectNotFound>)
    {
        if(!bias)
            throw E<Exception::ObjectNotFound>()<<"Link::getBias(): No bias\n";

        return *bias;
    } //getBias

    const Weight&
    Neuron::getBias() const throw(E<Exception::ObjectNotFound>)
    {
        if(!bias)
            throw E<Exception::ObjectNotFound>()<<"Link::getBias(): No bias\n";

        return *bias;
    } //getBias

    void
    Neuron::fire()
    {
        activationFunction->fire(*this);
    } //fire

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
