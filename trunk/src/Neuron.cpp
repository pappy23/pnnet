//Neuron.cpp

#include "Neuron.h"

using std::list;

namespace pann
{
    Neuron::Neuron(ActivationFunction::Base& _activationFunction) :
            activationFunction(_activationFunction), 
            receptiveField(0), 
            activationValue(_activationFunction.f(0))
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    list<Link>::iterator Neuron::findLink(Neuron& _to)
    {
        list<Link>::iterator iter = links.begin(),
                             result = links.end();
        for(; iter != links.end(); ++iter)
        {
            if(&(iter->to) == &_to)
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

    float Neuron::activate()
    {
        return activationValue = activationFunction.f(receptiveField);
    } //activate

    void Neuron::connect(Neuron& _to, float _weightValue = 1)
    {
        connect(_to, new Weight(_weightValue)); 
    } //connectTo

    void Neuron::connect(Neuron& _to, Weight* _weight)
    {
        //ACHTUNG!!! Parallel links ARE allowed
        links.push_back( Link(_to, Link::out, _weight) ); //feedforward link
        _to.links.push_back( Link(*this, Link::in, _weight) ); //backpropagation link
    } //connectTo

    void Neuron::disconnect(Neuron& _from)
    {
        links.erase( findLink(_from) );
    } //disconnect

}; //pann
