
#include <stdio.h>

template <typename T>
class T1
{
public:
    T1(T *_a){ a = _a;}
    ~T1(){}

    T *a;
};

template <typename T>
class T2
{
public:
    T2(T1<int> *_a, T* _b){a = _a; b = _b;}
    ~T2(){}

    T1<int> *a;
    T *b;
};

int main()
{
    int a = 1;
    int b = 2;
    T1<int> t1(&a);
    T2<int> t2(&t1, &b);
    printf("%d-%d\n", *t2.a->a, *t2.b);

    return 0;
}
