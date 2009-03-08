//Neuron.cpp

#include "Neuron.h"

using std::list;
using boost::shared_ptr;

namespace pann
{
    Neuron::Neuron() :
            activationFunction(ActivationFunction::Linear::Instance()), 
            receptiveField(0), 
            activationValue(activationFunction.f(0)),
            a_hops(0),
            ownerThread(0)
    {
    } //Neuron

    Neuron::Neuron(ActivationFunction::Base& _activationFunction) :
            activationFunction(_activationFunction), 
            receptiveField(0), 
            activationValue(_activationFunction.f(0)),
            a_hops(0),
            ownerThread(0)
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
        connect( _to, shared_ptr<Weight>(new Weight(_weightValue)) ); 
    } //connectTo

    void Neuron::connect(Neuron& _to, shared_ptr<Weight> _weight)
    {
        //ACHTUNG!!! Parallel links ARE allowed
        links.push_back( Link(_to, Link::out, _weight) ); //feedforward link
        _to.links.push_back( Link(*this, Link::in, _weight) ); //backpropagation link
    } //connectTo

    void Neuron::disconnect(Neuron& _from)
    {
        links.erase( findLink(_from) );
    } //disconnect

    void Neuron::setOwnerThread(int _thread)
    {
        if(0 > _thread || _thread > 100)
            throw Exception::RangeMismatch()<<"Neuron::setOwnerThread(): thread must be between 0 and 100\n";

        ownerThread =_thread;
    } //setOwnerThread

}; //pann
