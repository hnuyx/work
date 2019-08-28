#include <stdio.h>

#include <cmath>

int main()
{
    for (int i = 0; i < 10; i ++)
        printf("%f\n", std::pow(10, i));
    return 0;
}
