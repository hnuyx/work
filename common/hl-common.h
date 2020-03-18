
/**
 * hl-common.h
 * common
 * Henry 2019-05-14
 * */

#ifndef __HL_COMMON_H__
#define __HL_COMMON_H__

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

#endif
