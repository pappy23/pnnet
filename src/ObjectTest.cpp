//ObjectTest.cpp

#include <boost/any.hpp>
#include <iostream>

#include "Object.h"

using namespace std;
using boost::any_cast;
using pann::Object;

int main(int argc, char* argv[])
{
    Object o(5);

    o["test1"] = float(8.978);
    o["test2"] = string("const1");

    cout<<o.id()<<endl;
    cout<<"test1: "<<any_cast<float>(o["test1"])<<endl;
    cout<<"test2: "<<any_cast<string>(o["test2"])<<endl;

    return 0;
}

