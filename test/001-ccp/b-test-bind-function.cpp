
#include <stdio.h>
#include <functional>

using namespace std;
using namespace std::placeholders;

class A;

typedef void (A::*pFunc)();
typedef void (*pFunc2)();
typedef function<void()> pFunc3;

//void Hello(pFunc2 pf)
void Hello(pFunc3 pf)
{
    pf();
}

class A
{
public:
    A()
    {
        v = 1;
        pf = &A::test;
    }

    ~A(){}

    void test()
    {
        printf("A::test(), V = %d\n", v);
    }

    int v;

    pFunc pf;

    void handle()
    {
        //Hello((pFunc2)pf);
        pFunc3 fun = bind(&A::test, this);
        //Hello((pFunc2)fun);
        Hello(fun);
    }

private:

};

int main()
{
    printf("Hello b-test\n");
    A a,b;
    a.v = 1;
    b.v = 2;
    a.handle();
    b.handle();
    printf("%d, %d\n", a.v, b.v);
    return 0;
}
