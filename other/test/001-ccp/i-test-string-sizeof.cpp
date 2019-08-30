
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
        T *t = (T *) malloc(sizeof(T));
        t->a.assign(b);
        free(t);
    }

    printf("%s, %s\n", a.c_str(), b.c_str());
    printf("%u, %u\n", sizeof(a), sizeof(b));
    return 0;
}
