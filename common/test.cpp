
#include <stdio.h>

#include "hl-time.h"

void test_auto_timer()
{
    HLAutoTimer timer("test_auto_timer");

    int sum = 0;
    for(int i = 0; i < 1000000; ++i) 
    {
        sum += i;
    }
}

int main()
{
    test_auto_timer();

    return 0;
}
