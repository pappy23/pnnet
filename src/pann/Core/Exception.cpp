//Exception.cpp

#include "Exception.h"

namespace pann
{
    namespace Exception
    {
        Base::Base() throw()
        {
        } //Base

        Base::Base(const Base& _rvalue) throw()
        {
            textStream << _rvalue.textStream.str();
        } //Base

        Base::~Base() throw()
        {
        } //~Base

        const char*
        Base::what() const throw()
        {
            return textStream.str().c_str();
        } //what

    }; //Exception
}; //pann

