/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include <boost/foreach.hpp>

#include "ActivationFunction.h"

#include "Neuron.h"
#include "Link.h"
#include "Weight.h"

BOOST_CLASS_EXPORT(pann::ActivationFunction::Linear);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Threshold);
BOOST_CLASS_EXPORT(pann::ActivationFunction::TanH);

namespace pann
{
    namespace ActivationFunction
    {
        void
        boost_export() throw()
        {
            //Current registration is very dirty, may be one time i'll fix it :)
            Linear::Instance();
            Threshold::Instance();
            TanH::Instance();
        } //boost_export

        Base* Linear::self = 0;

        Linear::Linear() throw()
        {
        } //Linear

        Linear::~Linear() throw()
        {
            self = 0;
        } //~Linear

        Base*
        Linear::Instance() throw()
        {
            if(!self)
                self = new Linear();

            return self;
        } //Instance

        Float
        Linear::f(Float _x) const throw()
        {
            return _x;
        } //f

        Float
        Linear::derivative_dy(Float) const throw()
        {
            return 1;
        } //derivative_dy

        void
        Linear::fire(Neuron& _n)
        {
            _n[Neuron::receptiveField] = 0;

            if(_n.hasBias())
                _n[Neuron::receptiveField] += _n.getBias()[Weight::value];

            BOOST_FOREACH( Link& link, _n.links )
                if(link.getDirection() == Link::in)
                    _n[Neuron::receptiveField] += link.getTo()[Neuron::activationValue] * link.getWeight()[Weight::value];

            _n[Neuron::activationValue] = _n.getActivationFunction().f(_n[Neuron::receptiveField]);
        } //fire

        Base* Threshold::self = 0;

        Threshold::Threshold() throw()
        {
        } //Threshold

        Threshold::~Threshold() throw()
        {
            self = 0;
        } //~Threshold

        Base*
        Threshold::Instance() throw()
        {
            if(!self)
                self = new Threshold();

            return self;
        } //Instance

        Float
        Threshold::f(Float _x) const throw()
        {
            if(_x < 0)
                return 0;
            return 1;
        } //f

        Float
        Threshold::derivative_dy(Float) const throw()
        {
            return 0;
        } //derivative_dy

        void
        Threshold::fire(Neuron& _n)
        {
            _n[Neuron::receptiveField] = 0;

            if(_n.hasBias())
                _n[Neuron::receptiveField] += _n.getBias()[Weight::value];

            BOOST_FOREACH( Link& link, _n.links )
                if(link.getDirection() == Link::in)
                    _n[Neuron::receptiveField] += link.getTo()[Neuron::activationValue] * link.getWeight()[Weight::value];

            _n[Neuron::activationValue] = _n.getActivationFunction().f(_n[Neuron::receptiveField]);
        } //fire

        Base* TanH::self = 0;
        const Float TanH::a = 1.7159;
        const Float TanH::b = 0.6667;

        TanH::TanH() throw()
        {
        } //TanH

        TanH::~TanH() throw()
        {
            self = 0;
        } //~TanH

        Base*
        TanH::Instance() throw()
        {
            if(!self)
                self = new TanH();

            return self;
        } //Instance

        Float
        TanH::f(Float _x) const throw()
        {
            return a * std::tanh( b * _x );
        } //f

        Float
        TanH::derivative_dy(Float _y) const throw()
        {
            return b/a * (a - _y) * (a + _y);
        } //derivative_dy

        void
        TanH::fire(Neuron& _n)
        {
            _n[Neuron::receptiveField] = 0;

            if(_n.hasBias())
                _n[Neuron::receptiveField] += _n.getBias()[Weight::value];

            BOOST_FOREACH( Link& link, _n.links )
                if(link.getDirection() == Link::in)
                    _n[Neuron::receptiveField] += link.getTo()[Neuron::activationValue] * link.getWeight()[Weight::value];

            _n[Neuron::activationValue] = _n.getActivationFunction().f(_n[Neuron::receptiveField]);
        } //fire

    }; //ActivationFunction
}; //pann

