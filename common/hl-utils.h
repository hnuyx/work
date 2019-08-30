
/**
 * hl-utils.h
 * utils
 * Henry 2019-05-14
 * */

#ifndef __HL_UTILES_H__
#define __HL_UTILES_H__

#include <string.h>

#define HL_CHECK_RESULT_RETURN_VOID(r,e,s) \
    if (r == e) {              \
        printf("%s\n", s);     \
        return ;               \
    }

#define HL_CHECK_RESULT_RETURN(r,e,s,t) \
    if (r == e) {              \
        printf("%s\n", s);     \
        return t;              \
    }

#define HL_CHECK_RESULT_EXIT(r,e,s) \
    if (r == e) {              \
        printf("%s\n", s);     \
        exit(-1);              \
    }

#define HL_XFREE(b) \
    if (b) free(b); \
    b = NULL;

/**
 * copy file
 * src: filename of source file
 * dest: filename of destiantion file
 *
 * return 0 for success, -1 for failed
 * */
extern int cp_file(char *src, char* dest);

/**
 * load file
 * filename: file to be loaded
 * buf: store result into buf
 * size: size of buf
 *
 * return file size for success, -1 for failed
 * */
extern size_t load_file(const char *filename, char *buf, const size_t size);

#endif
