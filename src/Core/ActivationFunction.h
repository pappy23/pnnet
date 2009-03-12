/**
 * @file
 * Activation functions declarations
 */

#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

#include "Includes.h"
#include "Type.h"

namespace pann
{
    namespace ActivationFunction
    {
        /**
         * All activation functions inherit ActivationFunction::Base
         * and implement Instance() method
         * Base is a singleton pattern
         */
        class Base //Singleton
        {
        protected:
            static Base* self;

        protected:
			Base() { };

        public:
			virtual ~Base() { };

        public:
            //Returns reference to ActivationFunction object. It is always the same
            //Only one object of class Base exist at a time
            static Base* Instance();

            virtual Float f(Float) = 0;
            virtual Float derivative(Float) = 0;

        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                };
        };

        /**
         * Linear function
         * y = x
         * dy/dx = 0
         */
        class Linear : public Base
        {
		private:
			Linear() {};

        public:
			~Linear() {};

        public:
            static Base* Instance()
            {
                if(!self)
                    self = new Linear();

                return self;
            };

            Float f(Float _x)
            {
                return _x;
            } //f

            Float derivative(Float)
            {
                return 0;
            } //derivative

        private:
            friend class boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                };
        };
    }; //ActivationFunctions

}; //pann
#endif //ACTIVATIONFUNCTION_H

