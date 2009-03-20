//LearningHint.cpp

#include "LearningHint.h"

namespace pann
{
    namespace LearningHint
    {
        Null::Null()
        {
        } //Null

        Null::~Null()
        {
        } //~Null

        unsigned Null::getTypeId()
        {
            return 1;
        } //getTypeId

        Base*
        getById(unsigned _id)
        {
            switch(_id)
            {
            case 1:
                return (Base*)new Null;
                break;
            case 2:
                return (Base*)new LmsNet;
                break;
            case 3:
                return (Base*)new LmsNeuron;
                break;
            default:
                throw Exception::ObjectNotFound()<<"LearningHint::getById(): unknown hint id: "<<_id<<"\n";
            }
        } //getById

    }; //LearningHint
}; //pann
