
#include <stdio.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = shm_open("/mongoc-1234", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR | O_NOFOLLOW);
    printf("%d\n", fd);
    return 0;
}
