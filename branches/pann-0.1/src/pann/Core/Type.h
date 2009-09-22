/*
 * @file
 * Custom types declarations
 */

#ifndef TYPE_H
#define TYPE_H

#include "Includes/Std.h"
#include "Includes/BoostCommon.h"

namespace pann
{
    typedef double Float;
    const Float inf = std::numeric_limits<Float>::infinity();

    typedef std::size_t HashType;

/**
 * Use case: ADD_PTR_TYPEDEF(Neuron)
 */
#define ADD_PTR_TYPEDEF(C) \
    class C; \
    typedef boost::shared_ptr<C> C##Ptr; \
    typedef boost::shared_ptr<const C> C##ConstPtr;

    ADD_PTR_TYPEDEF(Runner);
    ADD_PTR_TYPEDEF(ActivationFunction);
    ADD_PTR_TYPEDEF(Neuron);
    ADD_PTR_TYPEDEF(Weight);
    ADD_PTR_TYPEDEF(Net);
    ADD_PTR_TYPEDEF(Attributes);

//May be replaced with templates<>
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
        };

#define SINGLETON_SKELETON(CLASS, BASE) \
    CLASS() {}; \
    SINGLETON_SKELETON_WITHOUT_CONSTRUCTOR(CLASS, BASE);

//Register singleton in .h file and don't use .cpp
/*
#define REGISTER_SINGLETON(C, T) \
    BOOST_CLASS_EXPORT(pann::C) \
    const pann::T##Ptr C##Register = pann::C::Instance();
*/

//Split registration
#define REGISTER_SINGLETON_H(C) \
    int register_singleton_##C(); \
    const int register_singleton_##C##_result = register_singleton_##C();

#define REGISTER_SINGLETON_CPP(C) \
    BOOST_CLASS_EXPORT(pann::C) \
    namespace pann { \
    int register_singleton_##C() \
    { \
        C::Instance(); \
        return 0; \
    }; \
    };

#define REGISTER_ATTRIBUTES_H(C) \
    int register_attributes_##C(); \
    const int register_attributes_##C##_result = register_attributes_##C();

#define REGISTER_ATTRIBUTES_CPP(C) \
    BOOST_CLASS_EXPORT(pann::C) \
    namespace pann { \
    int register_attributes_##C() \
    { \
        new C(); \
        return 0; \
    }; \
    };

}; //pann

#endif //TYPE_H

