#include <iostream>

using namespace std;

class A
{
public:
    static int val;
    static void f();
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

//    r2.val =7;
    return 0;
}
