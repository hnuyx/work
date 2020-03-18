
/**
 * hl-file.cpp
 * file
 * Henry 2019-05-14
 * */

#include "hl-file.h"

#include <stdio.h>

/**
 * copy file
 * src: filename of source file
 * dest: filename of destiantion file
 *
 * return 0 for success, -1 for failed
 * */
int cp_file(char *src, char* dest)
{
    FILE *fsrc, *fdest;
    char buffer[1024];
    size_t lsrc, ldest;

    fsrc = fopen(src, "r");
    if(NULL == fsrc)
    {
        printf("open src file %s failed\n", src);
        return -1;
    }

    fdest = fopen(dest, "w+");
    if(NULL == fdest)
    {
        printf("open dest file %s failed\n", dest);
        fclose(fsrc);
        return -1;
    }

    while((lsrc = fread(buffer, 1, 1024, fsrc)) > 0)
    {
        ldest = fwrite(buffer, 1, lsrc, fdest);
        if(lsrc != ldest)
        {
            printf("failed copy %lu bytes from %s to %s\n", lsrc, src, dest);
            fclose(fsrc);
            fclose(fdest);
            return -1;
        }
    }

    fclose(fsrc);
    fclose(fdest);

    return 0;
}

/**
 * load file
 * filename: file to be loaded
 * buf: store result into buf
 * size: size of buf
 *
 * return file size for success, -1 for failed
 * */
size_t load_file(const char *filename, char *buf, const size_t size)
{
    FILE *fp = fopen(filename, "r");
    if(NULL == fp)
    {
        printf("open file %s failed\n", filename);
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    size_t len = ftell(fp);
    if (len > size)
    {
        printf("file is too large %lu > %lu\n", len, size);
        return -1;
    }

    memset(buf, 0, size);
    fseek(fp, 0L, SEEK_SET);
    if(len != fread(buf, 1, len, fp))
    {
        printf("read file %s failed\n", filename);
        return -1;
    }

    fclose(fp);
    return len;
}
