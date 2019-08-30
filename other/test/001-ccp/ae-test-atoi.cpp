
#include <stdio.h>
#include <stdlib.h>


int main()
{
    const char *s1 = "SH600000";
    const char *s2 = "SZ000001";
    const char *s3 = "600000.SH";
    const char *s4 = "000001.SZ";

    printf("%d\n", atoi(s1 + 2));
    printf("%d\n", atoi(s2 + 2));
    printf("%d\n", atoi(s3));
    printf("%d\n", atoi(s4));

    return 0;
}
