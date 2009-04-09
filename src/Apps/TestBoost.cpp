#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

void hello()
{
    cout<<"hello\n";
}

int main()
{
    boost::thread t(hello);

    t.join();

    return 0;
}

