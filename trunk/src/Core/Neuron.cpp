//Neuron.cpp

#include "Neuron.h"

using namespace std;
using boost::shared_ptr;

namespace pann
{
    //! Deafult constructor
    Neuron::Neuron() :
            activationFunction(ActivationFunction::Linear::Instance()),
            receptiveField(0),
            activationValue(activationFunction.f(0)),
            ownerThread(0)
    {
    } //Neuron

    Neuron::Neuron(ActivationFunction::Base& _activationFunction) :
            activationFunction(_activationFunction),
            receptiveField(0),
            activationValue(_activationFunction.f(0)),
            ownerThread(0)
    {
    } //Neuron

    Neuron::~Neuron()
    {
    } //~Neuron

    list<Link>::iterator Neuron::findLink(NeuronIter _to, Link::Direction _direction)
    {
        list<Link>::iterator iter = links.begin(),
                             result = links.end();
        for(; iter != links.end(); ++iter)
        {
            if(iter->to == _to && iter->direction == _direction)
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

    void Neuron::activate()
    {
        activationValue = activationFunction.f(receptiveField);
        receptiveField = 0;
    } //activate

    void Neuron::connect(NeuronIter _to, Link::Direction _direction, Float _weightValue = 1)
    {
        connect( _to, _direction, shared_ptr<Weight>(new Weight(_weightValue)) );
    } //connectTo

    void Neuron::connect(NeuronIter _to, Link::Direction _direction, shared_ptr<Weight> _weight)
    {
        //FIXME Parallel links ARE allowed
        links.push_back( Link(_to, _direction, _weight) );
    } //connectTo

    void Neuron::disconnect(NeuronIter _to, Link::Direction _direction)
    {
        links.erase( findLink(_to, _direction) );
    } //disconnect

    void Neuron::setOwnerThread(int _thread)
    {
        if(0 > _thread || _thread > 100)
            throw Exception::RangeMismatch()<<"Neuron::setOwnerThread(): thread must be between 0 and 100\n";

        ownerThread =_thread;
    } //setOwnerThread

    void Neuron::printDebugInfo(ostringstream& ost)
    {
        ost<<" Neuron\n";
        ost<<"  ownerThread: "<<ownerThread<<std::endl;
        list<Link>::iterator it = links.begin();
        for(; it != links.end(); ++it)
            it->printDebugInfo(ost);
    } //printDebugInfo

    Float Neuron::getActivationValue()
    {
        return activationValue;
    }//getActivationValue

}; //pann
