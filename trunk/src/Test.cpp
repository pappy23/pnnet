#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

/*
 * Today we are testing boost::shared_ptr<>
 */
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
    A* ptr = new A(1);
    shared_ptr<A> ptr1( ptr );

    {
        cout<<"  {\n";
        shared_ptr<A> ptr2 ( ptr );
        cout<<"  }\n";
    }

    cout<<"} //main()\n";

    return 0;
}
