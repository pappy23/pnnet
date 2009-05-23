/**
 * @file
 * Defines and implements all exception related stuff
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Includes/Std.h"

namespace pann
{
    /**
     * Use case: throw E<Exception::CoolException>()<<"This is exception; i = "<<5<<std::endl;
     * Don't forget to declare your CoolException, derived from Exception::Base
     */
    namespace Exception
    {
        //! Not critical. Simply instantiate
        class Warning {};

        //! Reference to unexistent object was requested
        class ObjectNotFound {}; 
        
        //! Trying to add already existent element
        class ElementExists {}; 

        //! Multiple elements exist, but onlyone allowed; ex: parallel links between neurons are not allowed
        class MultipleOccurance {}; 

        //! Count of elements mismatch
        class SizeMismatch {}; 

        //! Argument out of range
        class RangeMismatch {}; 

        //! Requested not computed value
        class NotReady {}; 

        //! Exceptionfor raising on filesystem failures (missing file etc.) 
        class FilesystemError {}; 

        //! It's imposible in our universe!
        class Unbelievable {}; 


	
	class Exp : public std::exception
	{
	private:
	
		std::string msg;
	public :
		Exp() {msg="";};
	
		Exp( const Exp &rhs )
		{
			msg = rhs.msg;
		}
	
		virtual ~Exp() throw(){};
	
		virtual const char * what() const throw()
		{
			return msg.c_str();
		}
	
	
		template<typename T>
		Exp& operator<<( const T& t )
		{
			std::stringstream ss;
			ss <<t;
			msg +=ss.str();
			return *this;
		}
	
	};

    }; //Exception

    template<class C>
    class E : public std::exception
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
        std::cerr << _value;

        return *this;
    } //operator<<

}; //pann

#endif
