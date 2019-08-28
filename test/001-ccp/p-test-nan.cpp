
#include <stdio.h>
#include <iostream>
#include <cmath>

int  main()
{
    double a = std::nan("1");
    double b = std::nan("1");

    std::cout<< a+b+1 << std::endl;
}
