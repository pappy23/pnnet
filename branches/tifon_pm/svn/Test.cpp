#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;


class A
{
};

class B : public A
{
};

class C : public A
{
//    static string = string("test");
};

int main()
{
    B *obj = new B;
    A *a_ptr = dynamic_cast<A*>(obj);
    C *c_ptr = dynamic_cast<C*>(obj);
/*
    vector< shared_ptr<A> > vec;

    for(int i = 0; i < 10; i++)
    {
        vec.push_back(shared_ptr<A>(new A));
    }

    cout<<"VAL="<<vec[5]->val<<endl;
*/    
    return 0;
}
