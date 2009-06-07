
#include "ActivationFunction.h"

BOOST_CLASS_EXPORT(pann::ActivationFunction::Linear);
BOOST_CLASS_EXPORT(pann::ActivationFunction::Threshold);
BOOST_CLASS_EXPORT(pann::ActivationFunction::TanH);

namespace pann
{
    namespace ActivationFunction
    {
        void
        boost_export()
        {
            //Current registration is very dirty, may be one time i'll fix it :)
            Linear::Instance();
            Threshold::Instance();
            TanH::Instance();
        } //boost_export


        Base* Linear::self = 0;

        Linear::Linear()
        {
        } //Linear

        Linear::~Linear()
        {
            self = 0;
        } //~Linear

        Base*
        Linear::Instance()
        {
            if(!self)
                self = new Linear();

            return self;
        } //Instance

        Float
        Linear::f(Float _x) const
        {
            return _x;
        } //f

        Float
        Linear::derivative_dy(Float) const
        {
            return 1;
        } //derivative_dy


        Base* Threshold::self = 0;

        Threshold::Threshold()
        {
        } //Threshold

        Threshold::~Threshold()
        {
            self = 0;
        } //~Threshold

        Base*
        Threshold::Instance()
        {
            if(!self)
                self = new Threshold();

            return self;
        } //Instance

        Float
        Threshold::f(Float _x) const
        {
            if(_x < 0)
                return 0;
            return 1;
        } //f

        Float
        Threshold::derivative_dy(Float _x) const
        {
            if(_x == 0)
                return inf;

            return 0;
        } //derivative_dy


        Base* TanH::self = 0;
        const Float TanH::a = 1.7159;
        const Float TanH::b = 0.6667;

        TanH::TanH()
        {
        } //TanH

        TanH::~TanH()
        {
            self = 0;
        } //~TanH

        Base*
        TanH::Instance()
        {
            if(!self)
                self = new TanH();

            return self;
        } //Instance

        Float
        TanH::f(Float _x) const
        {
            return a * std::tanh( b * _x );
        } //f

        Float
        TanH::derivative_dy(Float _y) const
        {
            return b/a * (a - _y) * (a + _y);
        } //derivative_dy

    }; //ActivationFunction
}; //pann

