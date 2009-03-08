/**
 * @file
 * Defines and implements all exception related stuff
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Includes.h"

namespace pann
{
    /**
     * Use case: throw Exception::CoolException()<<"This is exception; i = "<<5<<std::endl;
     * Don't forget to declare your CoolException, derived from Exception::Base
     */
    namespace Exception
    {
        //! Basic class for every exception
        class Base
        {
        protected:
            std::ostringstream textStream;

        public:
            Base()
            {
                std::cerr<<"ACTUNG!!! ";
            };

            Base(Base& _rvalue) : textStream(_rvalue.textStream.str()) { };

            virtual ~Base() { };

            std::string text()
            {
                return textStream.str();
            };

            template<typename T> Base& operator<<(const T& value)
            {
                textStream << value;
                std::cerr << value;

                return *this;
            }
        };

        //! Reference to unexistent object was requested
        class ObjectNotFound : public Base { }; 
        
        //! Trying to add already existent element
        class ElementExists  : public Base { }; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance  : public Base { }; 

    }; //Exception

}; //pann

#endif
