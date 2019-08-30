
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <KData.h>

//#define LM_IPC_SHM_PATH   "/data/quant/"
#define LM_IPC_SHM_PATH   "."
#define LM_IPC_SHM_ID     0x20190709

class LMSHMBar
{
public:
    LMSHMBar(const char *pathname=LM_IPC_SHM_PATH, int proj_id=LM_IPC_SHM_ID)
    {
    }

    ~LMSHMBar()
    {
    }
};

#define LM_MIN_KLINE_COUNT 365*3

#pragma pack(push, 4)
typedef struct _MinKLineData
{
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
    uint64_t time;
    uint64_t ammount;
    uint64_t balance;
} MinKLineData;

typedef struct _MinKLine
{
    uint32_t flag;
    MinKLineData *data;
} MinKLine;

typedef struct _DayKLineData
{
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
    uint32_t prev_close;
    uint64_t time;
    uint64_t ammount;
    uint64_t balance;
} DayKLineData;

typedef struct _DayKLine
{
    uint32_t flag;
    DayKLineData *data;
} DayKLine;

#pragma pack(pop)

int main()
{
    uint32_t size = sizeof(MinKLine);
    printf("MinKLine size: %u\n", size);

    printf("MinKLineData size: %u\n", sizeof(MinKLineData));
    printf("DayKLineData size: %u\n", sizeof(DayKLineData));

    key_t key = ftok(LM_IPC_SHM_PATH, LM_IPC_SHM_ID);
    if (key < 0)
    {
        printf("ftok failed %d:%s\n", errno, strerror(errno));
        return -1;
    }
    printf("%u\n", key);

    //int shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
    int shmid = shmget(key, size, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        printf("shmget failed %d:%s\n", errno, strerror(errno));
        return -1;
    }
    printf("%d\n", shmid);

    char *addr = (char *)shmat(shmid, NULL, 0);
    if ((void *)-1 == (void *)addr)
    {
        printf("shmat failed %d:%s\n", errno, strerror(errno));
        return -1;
    }

    sleep(10);

    return 0;
}
