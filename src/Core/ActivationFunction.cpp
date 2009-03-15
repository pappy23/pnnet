/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

namespace pann
{
    namespace ActivationFunction
    {
        Base* Linear::self = 0;
        
        Base* Threshold::self = 0;

        Base* TanH::self = 0;
        const Float TanH::a = 1.7159;
        const Float TanH::b = 0.6667;

        Base*
        getById(const unsigned id)
        {
            switch(id)
            {
            case 1:
                return Linear::Instance();
                break;
            case 2:
                return Threshold::Instance();
                break;
            case 3:
                return TanH::Instance();
                break;
            default:
                throw Exception::ObjectNotFound()<<"ActivationFunction::getById(): unknown function id: "<<id<<"\n";
            };
        };
    }; //ActivationFunction
}; //pann

