
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LM_IPC_MMAP_KLINE_PATH   "/data/quant/kline"

#define LM_IS_KLINE_WRITE(f)         (f & 0x80000000)
#define LM_SET_KLINE_WRITE(f)        (f |= 0x80000000)
#define LM_CLR_KLINE_WRITE(f)        (f &= 0x7fffffff)
#define LM_KLINE_COUNT(f)            (f & 0x7fffffff)
#define LM_INCR_KLINE_COUNT(f, c)    (f += c)

#define LM_1M_KLINE_DAY_COUNT     242
#define LM_5M_KLINE_DAY_COUNT     50
#define LM_15M_KLINE_DAY_COUNT    18
#define LM_30M_KLINE_DAY_COUNT    10
#define LM_HOUR_KLINE_DAY_COUNT   6

#pragma pack(push, 4)
typedef struct _MinKLineData
{
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
    uint64_t time;
    uint64_t amount;
    uint64_t balance;
} MinKLineData;

typedef struct _DayKLineData
{
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
    uint32_t prev_close;
    uint64_t time;
    uint64_t amount;
    uint64_t balance;
} DayKLineData;

typedef struct _KLineStatus
{
    // flag: f------, flag + count
    uint32_t flag;
} KLineStatus;
#pragma pack(pop)

int main(int argc, char **argv)
{
    printf("MinKLineData size: %u\n", sizeof(MinKLineData));
    printf("DayKLineData size: %u\n", sizeof(DayKLineData));

    int ret;

    const char *filename="/data/quant/kline/1mkline/600572.SS";
    // open file, if not exist creat it with mode rw-r--r--
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        printf("open file %s error %d:%s\n", filename, errno, strerror(errno));
        return -1;
    }

    // get file size
    off_t size = lseek(fd, 0, SEEK_END);
    if (size < sizeof(KLineStatus))
    {
        ret = ftruncate(fd, sizeof(KLineStatus));
        if (ret < 0)
        {
            printf("truncate file %s size %d error %d:%s\n", filename, sizeof(KLineStatus), errno, strerror(errno));
            return -1 ;
        }
    }

    KLineStatus kls;

    // seek to begin
    lseek(fd, 0, SEEK_SET);
    ret = read(fd, &kls, sizeof(KLineStatus));
    if (ret < 0)
    {
        printf("read file %s error %d:%s\n", filename, errno, strerror(errno));
        return -1;
    }

    size = sizeof(KLineStatus) + LM_KLINE_COUNT(kls.flag) * sizeof(MinKLineData) + LM_1M_KLINE_DAY_COUNT * sizeof(MinKLineData);
    printf("be here 1, count: %d size: %d\n", LM_KLINE_COUNT(kls.flag), size);
    ret = ftruncate(fd, size);
    if (ret < 0)
    {
        printf("truncate file %s size %d error %d:%s\n", filename, size, errno, strerror(errno));
        return -1 ;
    }

    char *p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
    {
        printf("mmap file %s size %d error %d:%s\n", filename, size, errno, strerror(errno));
        return -1 ;
    }

    close(fd);

    KLineStatus *pkls = (KLineStatus *)p;
    p += sizeof(KLineStatus);
    MinKLineData *pkld = (MinKLineData *)p;
    p -= sizeof(KLineStatus);

    printf("%d, %s\n", argc, argv[1]);
    if (argc >= 2 && argv[1][0] == 'w')
    {
        int cnt = LM_KLINE_COUNT(pkls->flag);

        LM_SET_KLINE_WRITE(pkls->flag);
        for(uint32_t i = cnt; i < cnt + LM_1M_KLINE_DAY_COUNT; i ++)
        {
            MinKLineData mkd = {i, i, i, i, 201907092115, i, i};
            memcpy(pkld+i, &mkd, sizeof(MinKLineData));
            LM_INCR_KLINE_COUNT(pkls->flag, 1);
        }
        LM_CLR_KLINE_WRITE(pkls->flag);
    }
    else if (argc >= 2 && argv[1][0] == 'r')
    {
        int cnt = LM_KLINE_COUNT(pkls->flag);

        for(int i = 0; i < cnt; i ++)
        {
            printf("%u, %u, %u, %u, %llu, %llu, %llu\n",
                   pkld[i].open, pkld[i].high, pkld[i].low, pkld[i].close,
                   pkld[i].time, pkld[i].amount, pkld[i].balance);
        }
    }

    ret = munmap(p, size);
    if (ret < 0)
    {
        printf("munmap file %s size %d error %d:%s\n", filename, size, errno, strerror(errno));
        return -1 ;
    }

    return 0;
}
