/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::ActivationFunction::Linear);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Threshold);
BOOST_CLASS_EXPORT(pann::ActivationFunction::TanH);

namespace pann
{
    namespace ActivationFunction
    {
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
            return 0;
        } //derivative_dy

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

    }; //ActivationFunction
}; //pann

