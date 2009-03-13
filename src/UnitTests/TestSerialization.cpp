
//TestNet.cpp

#include <iostream>
#include <iomanip>

#include "Includes.h"
#include "ActivationFunction.h"

using namespace std;
using namespace pann;
using namespace boost;

class A
{
public:
    int a;

private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & a;
        };
};

class N
{
public:
    A* af;

private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & af;
        };
};

int main()
{
    vector<N> obj1, obj2;
        obj1.push_back(N());
        obj1[0].af = new A();
        obj1[0].af->a = 5;

    for(int i = 1; i < 10; i++)
    {
        obj1.push_back(N());
        obj1[i].af = obj1[0].af;
    }

    {
        ofstream ofs("ser.txt"); 
        boost::archive::text_oarchive oa(ofs);
        oa << obj1;
    }

    {
        ifstream ifs("ser.txt"); 
        boost::archive::text_iarchive ia(ifs);
        ia >> obj2;
    }

    for(int i = 0; i < 10; i++)
    {
        obj2[i].af->a = i;
    }

    for(int i = 0; i < 10; i++)
        cout<<obj2[i].af->a<<" ";

    return 0;
}

