#include <tbb/task_scheduler_init.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

using namespace tbb;

// 对每个元素执行该操作
void Foo(int value)
{
     // Applied function
    printf("%d\n", value);
}

class ApplyFoo
{
    int * const my_a;
public:
    void operator () (const blocked_range<size_t> & r) const
    {
        int * a = my_a;
        for (size_t i = r.begin(); i != r.end(); ++ i)
            Foo(a[i]);
    }

    ApplyFoo(int a[]) : my_a(a) {}
};

int main(int argc, char* argv[])
{
    // 创建task scheduler
    task_scheduler_init init;
    const int n = 100;
    int a[n];
    for (int i = 0; i < n; i ++)
        a[i] = i;

    // TBB会把数组分成若干的block
    // 对block调用ApplyFoo这个functor
    //parallel_for(blocked_range<size_t>(0, n), ApplyFoo(a), simple_partitioner());
    parallel_for(blocked_range<size_t>(0, n), ApplyFoo(a), simple_partitioner());
    return 0;
}
