
#include <stdio.h>
#include <stdint.h>

int main()
{
    double open, high, low, close, prev;
    uint64_t date, amount, balance;

    //const char *s = "201907171450,6.56,6.57,6.56,6.56,235300,1544332,49680257,322576002.00,49914257,324111806.00,201907171450,145015.200,1,stock,0.00,0";
    const char *s = "201907171450,6.56,6.57,6.56,6.56,235300,1544332,";

    sscanf(s, "%lu,%lf,%lf,%lf,%lf,%lu,%lu,",
           &date, &open, &high, &low, &close, &amount, &balance);

    printf("%lu %lf %lf %lf %lf %lu %lu\n", date, open, high, low, close, amount, balance);

    return 0;
}

