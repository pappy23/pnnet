
//TestNet.cpp

#include <iostream>

#include "Includes.h"

using namespace std;
using namespace boost;

class A
{
    virtual void test() {};
private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            cout<<"A\n";
        }
};

class Ader1 : public A
{
    virtual void test() {};
public:
    char b;

private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            cout<<"Ader1\n";
            ar & b;
        }
};

class Ader2 : public A
{
    virtual void test() {};
public:
    int a;

private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            cout<<"Ader2\n";
            ar & a;
        }
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
            cout<<"N\n";
            ar & af;
        };
};

int main()
{
    N obj1, obj2;

    obj1.af = new Ader1;
    (dynamic_cast<Ader1*>(obj1.af))->b = 5;

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

    cout<<dynamic_cast<Ader1*>(obj2.af)->b<<endl;

    return 0;
}

