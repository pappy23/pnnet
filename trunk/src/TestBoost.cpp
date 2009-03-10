#include <iostream>
#include <boost/thread.hpp>

using namespace std;

void print(int n)
{
    cout<<n<<" ";
}

int main()
{
    boost::thread_group pool;

    for(int i = 0; i < 10; i++)
        pool.add_thread(new boost::thread(print, i));

    return 0;
}

