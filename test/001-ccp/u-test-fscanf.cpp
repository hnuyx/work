
#include <stdio.h>

int main()
{
    FILE *fp = fopen("/data/quant/kline/stockst", "r");
    if (NULL == fp)
    {
        printf("open file failed\n");
        return -1;
    }

    char buf[12];
    snprintf(buf, 12, "%s", "12345678910");
    int cnt = 0;
    while(EOF != fscanf(fp, "%s", buf))
    {
        ++ cnt;
        printf("%s\n", buf);
    }
    printf("cnt: %d\n", cnt);

    return 0;
}
