
#include <stdio.h>

int main()
{
    int a = 10;
    int &b = a;
    printf("%d, %d\n", a, b);
    printf("%x\n%x\n", &a, &b);
    return 0;
}
