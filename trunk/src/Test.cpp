#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

class A
{
    int a;

public:
    A(int _a) : a(_a)
    {
        cout<<"Creating A("<<a<<")\n";
    };

    ~A()
    {
        cout<<"Destroying A("<<a<<")\n";
    };
};

int main()
{
    cout<<"main()\n{\n";
    shared_ptr<A> ptr1( new A(1) );

    {
        cout<<"  {\n";
        shared_ptr<A> ptr2 ( ptr1 );
        cout<<"  }\n";
    }

    cout<<"} //main()\n";

    return 0;
}
