
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#pragma pack(push, 4)
#pragma pack(pop)

int main(int argc, char **argv)
{
    int ret;

    //const char *filename = "/data/quant/build/kfc";
    const char *filename = "/dev/zero";
    // open file, if not exist creat it with mode rw-r--r--
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd < 0)
    {
        printf("open file %s error %d:%s\n", filename, errno, strerror(errno));
        return -1;
    }

#if 0 
    ret = ftruncate(fd, sizeof(int));
    if (ret < 0)
    {
        printf("truncate file %s size %d error %d:%s\n", filename, sizeof(int), errno, strerror(errno));
        return -1 ;
    }
#endif

    int *p = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
    {
        printf("mmap file %s size %d error %d:%s\n", filename, sizeof(int), errno, strerror(errno));
        return -1 ;
    }

    close(fd);

    if (argc >= 2 && argv[1][0] == 'w')
    {
        while(true)
        {
            (*p) += 1;
            printf("write value: %d\n", *p);
            sleep(1);
        }
    }
    else if (argc >= 2 && argv[1][0] == 'r')
    {
        while(true)
        {
            printf("read value: %d\n", *p);
            sleep(1);
        }
    }

    ret = munmap(p, sizeof(int));
    if (ret < 0)
    {
        printf("munmap file %s size %d error %d:%s\n", filename, sizeof(int), errno, strerror(errno));
        return -1 ;
    }

    return 0;
}
