
#include <stdio.h>

class Base
{
public:
    Base() {}
    virtual ~Base() {}

    virtual void func(int t) = 0;
};

template<int id>
class A : public Base
{
public:
    A() {};
    ~A() {};

    void func(int t)
    {
        printf("%d-%d\n", id, t);
    }
};

typedef class A<1> Ia;
typedef class A<2> Ib;

Ia a;
Ib b;

Base* array[2] = {&a, &b};

Base *getC(int i)
{
    return array[i];
}

int main()
{
    for (int i = 0; i < 2; i ++)
    {
        Base *t = array[i];
        t->func(i);
    }
}
