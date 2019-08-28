
#include <stdio.h>

class NullBase
{};

class Base
{
public:
    int a;
    int b;
    int c;
    int d;
    virtual int func() = 0;
    virtual int func2() = 0;
    virtual int func3() = 0;
};

int main()
{
    printf("NullBase size: %d\n", sizeof(NullBase));
    printf("virtual Base size: %d\n", sizeof(Base));
    return 0;
}
