#include <iostream>
#include <map>
//#include <boost/shared_ptr.hpp>

using namespace std;
//using namespace boost;

class A;

typedef map<int, A>::iterator It;

class B
{
    int b;
    It i;
};

class A
{
    int a;
    B link;
};


int main()
{
    map<int, A> m;
}
