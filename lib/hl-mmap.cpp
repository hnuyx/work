/* hl-mmap.cpp
 *
 * mmap operations
 * */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hl-mmap.h"

/* get mmap
 * filename: file name will mmap
 * leght: file length
 * is_write: true for write, false for read
 *
 * return non-null for success, null for failed
 * */
void* get_mmap(const char *filename, size_t length, bool is_write)
{
    int fd = 0, ret = 0;
    void *p = NULL;
    // open file
    if (is_write)
        fd = open(filename, O_RDWR | O_CREAT, 0644);
    else
        fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("open file %s error %d:%s\n", filename, errno, strerror(errno));
        return NULL;
    }

    if (is_write)
    {
        //  truncate file size
        ret = ftruncate(fd, length);
        if (ret < 0)
        {
            printf("truncate file %s lenght %lu error %d:%s\n", filename, length, errno, strerror(errno));
            close(fd);
            return NULL ;
        }
    }

    if (is_write)
        p = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    else
        p = mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED)
    {
        printf("mmap file %s length %lu error %d:%s\n", filename, length, errno, strerror(errno));
        close(fd);
        return NULL;
    }
    close(fd);

    return p;
}

/* delete mmap
 * info: output info when error happens
 * p: memory wil be delete
 * length: memory length
 *
 * */
void delete_mmap(const char *info, void *p, size_t length)
{
    if (p && length && munmap(p, length) < 0)
    {
        printf("munmap %s error %d:%s\n", info, errno, strerror(errno));
    }

    return ;
}
