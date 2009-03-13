/**
 * @file
 * Initialization of ActivationFunction::Base static members
 */

#include "ActivationFunction.h"

namespace pann
{
    namespace ActivationFunction
    {
        Base* Base::self = 0;

        Base* getById(const UINT id)
        {
            switch(id)
            {
            case 1:
                return Linear::Instance();
                break;
            default:
                throw Exception::ObjectNotFound()<<"ActivationFunction::getById(): unknown function id: "<<id<<"\n";
            };
        };
    }; //ActivationFunction
}; //pann

