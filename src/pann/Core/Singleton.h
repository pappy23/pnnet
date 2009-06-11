//Singleton.h

#ifndef SINGLETON_H
#define SINGLETON_H

#include "Type.h"

namespace pann
{
    class Singleton
    {
    public:
        virtual HashType getHash() = 0;
    }; //Singleton
    ADD_PTR_TYPEDEF(Singleton);

    template<class S>
    class SingltonRegister
    {
        SingletonPtr getSingleton()
        {
            return (Singleton*)(0);
        };
    }; //SingltonRegister

    template<class S>
    class SingltonRegister
    {
        SingletonPtr getSingleton()
        {
            return (Singleton*)(0);
        };
    }; //SingltonRegister

}; //pann

//#define REGISTER_SINGLETON(C, T) \
    BOOST_CLASS_EXPORT(pann::C) \
    const pann::T##Ptr C##Register = pann::C::Instance();

#define REGISTER_SINGLETON(C, T) \
    BOOST_CLASS_EXPORT(pann::C) \
    const pann::T##Ptr C##Register = pann::C::Instance();

#define SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(CLASS, BASE) \
    friend class boost::serialization::access; \
    template<class Archive> \
    void serialize(Archive & ar, const unsigned int version) \
    { \
        boost::serialization::void_cast_register<CLASS, BASE>( \
            static_cast<CLASS*>(NULL), \
            static_cast<BASE*>(NULL)); \
    }; \
    public: \
        static BASE##Ptr Instance() \
        { \
            static BASE##Ptr self(new CLASS()); \
            return self; \
        }; \
        \
        virtual HashType getHash() { return hash(#CLASS); };

#define SINGLETON_SKELETON(CLASS, BASE) \
    CLASS() {}; \
    SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(CLASS, BASE);

#endif

