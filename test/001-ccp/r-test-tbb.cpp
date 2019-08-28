
//#include <tbb/task_scheduler_init.h>
//#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
//#include <tbb/parallel_for_each.h>
//#include <tbb/task_scheduler_init.h>

#include <iostream>

using namespace std;


int main()
{
    //tbb::task_scheduler_init init;
    tbb::parallel_for(1, 100, [](int i){cout << i << endl; });

    return 0;
}
