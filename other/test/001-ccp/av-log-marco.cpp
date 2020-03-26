
#include <stdio.h>
#include <time.h>

#define LOG(...) \
    printf("%s %s:%d %s ", get_logger_time(), __FILE__, __LINE__, __func__); \
    printf(__VA_ARGS__); \
    printf("\n");

#define TIME_FORMAT_MAXSIZE 32

const char *get_logger_time()
{
    static char time_buf[TIME_FORMAT_MAXSIZE] = {'\0'};
    time_t t = time(NULL);
    struct tm *tm_tmp = localtime(&t);
    if(!tm_tmp)
        return time_buf;

    strftime(time_buf, TIME_FORMAT_MAXSIZE, "%Y-%m-%d %H:%M:%S", tm_tmp);
    return time_buf;
}

int main()
{
    LOG("%s", "i'm here");
    return 0;
}
