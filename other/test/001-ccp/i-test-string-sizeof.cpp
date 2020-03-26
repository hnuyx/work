
#include <stdio.h>
#include <string>
using namespace std;

struct T
{
    string a;
};

int main()
{
    string a, b;
    a = "abc";
    b = a;
    b = "cdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 10; i ++)
    {
        T *t = new T();
        t->a.assign(b);
        printf("t.a: %s\n", t->a.c_str());
        free(t);
    }

    printf("%s, %s\n", a.c_str(), b.c_str());
    printf("%u, %u\n", sizeof(a), sizeof(b));
    return 0;
}
