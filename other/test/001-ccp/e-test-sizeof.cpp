
#include <stdio.h>

class NullBase
{};


class Base01
{
public:
    static int a;
    static int func() {return 0;}
};

class Base1
{
public:
    virtual int func() = 0;
};

class Base2
{
public:
    virtual int func() = 0;
    virtual int func2() = 0;
    virtual int func3() = 0;
    virtual int func4() = 0;
};

class Base3
{
public:
    virtual int func() = 0;
    virtual int func2() = 0;
    virtual int func3() = 0;
    virtual int func4() = 0;

    int func5()
    {
        return 0;
    }
};

class Base4
{
private:
    int a;
    int b;
public:
    int c;
    int d;
    virtual int func() = 0;
    virtual int func2() = 0;
    virtual int func3() = 0;
};

class Base5
{
private:
    static int a;
    static int b;
public:
    int c;
    int d;
    virtual int func() = 0;
    virtual int func2() = 0;
    virtual int func3() = 0;
};

int main()
{
    printf("NullBase size: %d\n", sizeof(NullBase));
    printf("Base01 size: %d\n", sizeof(Base01));
    printf("Base1 size: %d\n", sizeof(Base1));
    printf("Base2 size: %d\n", sizeof(Base2));
    printf("Base3 size: %d\n", sizeof(Base3));
    printf("Base4 size: %d\n", sizeof(Base4));
    printf("Base5 size: %d\n", sizeof(Base5));
    return 0;
}
