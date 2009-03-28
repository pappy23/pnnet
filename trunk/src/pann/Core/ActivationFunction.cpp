/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::ActivationFunction::Bias);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Linear);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Threshold);
BOOST_CLASS_EXPORT(pann::ActivationFunction::TanH);

namespace pann
{
    namespace ActivationFunction
    {
        Base* Bias::self = 0;

        Bias::Bias() throw()
        {
        } //Bias

        Bias::~Bias() throw()
        {
            self = 0;
        } //~Bias

        Base*
        Bias::Instance() throw()
        {
            if(!self)
                self = new Bias();

            return self;
        } //Instance

        Float
        Bias::f(Float _x) const throw()
        {
            return 1;
        } //f

        Float 
        Bias::derivative(Float) const throw()
        {
            return 0;
        } //derivative

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
        Linear::derivative(Float) const throw()
        {
            return 0;
        } //derivative

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
        Threshold::derivative(Float _x) const throw()
        {
            if(_x == 0)
                return inf;
            return 0;
        } //derivative

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
        TanH::derivative(Float _x) const throw()
        {
            //FIXME
            return 0;
        } //derivative

    }; //ActivationFunction
}; //pann

