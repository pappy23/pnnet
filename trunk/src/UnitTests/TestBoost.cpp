#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//using namespace boost;

class A
{
public:
    int a;
};

class comp
{
public:
    bool operator()(const A& _lhs, const A& _rhs)
    {
        return _lhs.a == _rhs.a;
    }
};

int main()
{
    vector<A> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(A());
        v[i*2].a = i;
        v.push_back(A());
        v[i*2+1].a = i;
    }

    cout<<v.size()<<endl;

    vector<A>::iterator it = unique(v.begin(), v.end(), comp());
    v.resize( it - v.begin() );

    cout<<v.size()<<endl;

    return 0;
}

