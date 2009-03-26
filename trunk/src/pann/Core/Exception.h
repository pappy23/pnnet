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
     * Use case: throw E<Exception::CoolException>()<<"This is exception; i = "<<5<<std::endl;
     * Don't forget to declare your CoolException, derived from Exception::Base
     */
    namespace Exception
    {
        //! Basic class for every exception
        class Base : public std::exception {};

        //! Not critical. Simply instantiate
        class Warning : public Base {};

        //! Reference to unexistent object was requested
        class ObjectNotFound : public Base {}; 
        
        //! Trying to add already existent element
        class ElementExists  : public Base {}; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance  : public Base {}; 

        //! Count of elements mismatch
        class SizeMismatch  : public Base {}; 

        //! Argument out of range
        class RangeMismatch  : public Base {}; 

        //! Requested not computed value
        class NotReady  : public Base {}; 

        //! Exceptionfor raising on filesystem failures (missing file etc.) 
        class FilesystemError  : public Base {}; 

        //! It's imposible in our universe!
        class Unbelievable  : public Base {}; 

    }; //Exception

    template<class C>
    class E
    {
    public:
        E() throw();
        E(const E& _rvalue) throw();
        virtual ~E() throw();

        virtual const char* what() const throw();

        template<class T>
            E& operator<<(const T& _value) throw();

    protected:
        std::ostringstream textStream;
    };

    template<class C>
    E<C>::E() throw()
    {
    } //E

    template<class C>
    E<C>::E(const E<C>& _rvalue) throw()
    {
        textStream << _rvalue.textStream.str();
    } //E

    template<class C>
    E<C>::~E() throw()
    {
    } //~E

    template<class C>
    const char*
    E<C>::what() const throw()
    {
        return textStream.str().c_str();
    } //what

    template<class C>
        template<class T>
    E<C>&
    E<C>::operator<<(const T& _value) throw()
    {
        textStream << _value;
        std::cerr << _value << std::endl;

        return *this;
    } //operator<<

}; //pann

#endif
