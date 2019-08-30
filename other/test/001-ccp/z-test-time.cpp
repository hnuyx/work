
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string>

void print_mktime(uint64_t t)
{
    t /= 1000000;

    struct tm tm_tmp = {0};
    tm_tmp.tm_mday = t % 100;
    t /= 100;
    tm_tmp.tm_mon = t % 100 - 1;
    t /= 100;
    tm_tmp.tm_year = t - 1900;

    printf("%d %d %d\n", tm_tmp.tm_year + 1900, tm_tmp.tm_mon + 1, tm_tmp.tm_mday);
    printf("%u\n", mktime(&tm_tmp));
}

int main()
{
    print_mktime(20190718150000);
    print_mktime(20190719150000);

    return 0;
}
