
/**
 * hl-file.h
 * file 
 * Henry 2019-05-14
 * */

#ifndef __HL_FILE_H__
#define __HL_FILE_H__

#include <string.h>

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
