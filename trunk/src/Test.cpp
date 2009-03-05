#include <iostream>

using namespace std;

class A
{
public:
    int val;
};

class B : public A
{
public:
    int val2;
};

int main()
{
    B o;
    A & r1 = o;
    A & r2 = r1;


    return 0;
}
