
/**
 * hl-common.cpp
 * common tools
 * Henry 2019-08-29
 * */

#include "hl-common.h"

// get now time, YYYYMMDDHHMMSS
uint64_t get_now()
{
    return get_time(time(NULL));
}

// get date, YYYYMMDD
uint32_t get_date(time_t t)
{
    return (uint32_t)(get_time(t) / 1000000);
}

// get t time, YYYYMMDDHHMMSS
uint64_t get_time(time_t t)
{
    struct tm *tm_tmp;
    char time_buf[HL_TIME_MAX_SIZE];

    tm_tmp = localtime(&t);
    if(!tm_tmp)
    {
        printf("get localtime failed\n");
        return 0;
    }

    if(strftime(time_buf, HL_TIME_MAX_SIZE, "%Y%m%d%H%M%S", tm_tmp) == 0)
    {
        printf("strftime failed\n");
        return 0;
    }

    return std::stoul(time_buf);
}

// same day
bool is_same_day(uint64_t t1, uint64_t t2)
{
    return (t1 / 1000000 == t2 / 1000000);
}

// get week
// 0-N from 1900-01-01
// t: 20190829150000
uint64_t get_week(uint64_t t)
{
    struct tm tm_tmp = {0};

    t /= 1000000;
    tm_tmp.tm_mday = t % 100;
    t /= 100;
    tm_tmp.tm_mon = t % 100 - 1;
    t /= 100;
    tm_tmp.tm_year = t - 1900;

    return (mktime(&tm_tmp) - HL_MONDAY_BASE) / HL_WEEK_SECONDS;

}

