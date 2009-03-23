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
        //TODO Inherit from std::exception or std::runtime_exception
        class Base
        {
        protected:
            std::ostringstream textStream;

        public:
            Base()
            {
                std::cerr<<"ACHTUNG!!! ";
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
            };

            virtual std::string getText()
            {
                return textStream.str();
            };
        };

        //FIXME Don't know why, but programs threat all exceptions as Exception::Base type. May be we should
        //define constructors?

        //! Not critical. Simply instantiate
        class Warning : public Base { };

        //! Reference to unexistent object was requested
        class ObjectNotFound : public Base { }; 
        
        //! Trying to add already existent element
        class ElementExists  : public Base { }; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance  : public Base { }; 

        //! Count of elements mismatch
        class SizeMismatch  : public Base { }; 

        //! Argument out of range
        class RangeMismatch  : public Base { }; 

        //! Requested not computed value
        class NotReady  : public Base { }; 

        //! Exceptionfor raising on filesystem failures (missing file etc.) 
        class FilesystemError  : public Base { }; 

        //! It's imposible in our universe!
        class Unbelievable  : public Base { }; 

    }; //Exception

}; //pann

#endif
