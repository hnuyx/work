
/**
 * hl-time.h
 * time tools
 * Henry 2019-08-29
 * */

#ifndef __HL_TIME_H__
#define __HL_TIME_H__

#include <time.h>
#include <stdint.h>
#include <string>
#include <sys/time.h>

// seconds for 1 day
#define HL_DAY_SECONDS                      (24 * 60 * 60)
// seconds for one week
#define HL_WEEK_SECONDS                     (7 * HL_DAY_SECONDS)
// seconds for 1 year
#define HL_YEAR_SECONDS                     (365 * HL_DAY_SECONDS)
// monday base: 1990-01-01 00:00:00
#define HL_MONDAY_BASE                      631123200

// auto timer
#define ADJUST_TIME(se,ue,us) \
        if (ue < us) { ue += 1000000; se -= 1; }
class HLAutoTimer
{
public:
    HLAutoTimer(std::string info)
    {
        _info = info;
        gettimeofday(&start, NULL);
    }

    ~HLAutoTimer()
    {
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("%s: %lu.%06lu\n", _info.c_str(),
               (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
    }

private:
    struct timeval start, end;
    std::string _info;
};

// get now time, YYYYMMDDHHMMSS
uint64_t get_now();

// get date, YYYYMMDD
uint32_t get_date(time_t t);

// get t time, YYYYMMDDHHMMSS
uint64_t get_time(time_t t);

// same day
bool is_same_day(uint64_t t1, uint64_t t2);

// get week
// 0-N from 1900-01-01
// t: 20190829150000
uint64_t get_week(uint64_t t);

#endif
