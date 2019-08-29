/* hl-mmap.h
 *
 * mmap operations
 * */

#ifndef __HL_MMAP_H__
#define __HL_MMAP_H__

/* get mmap
 * filename: file name will mmap
 * leght: file length
 * is_write: true for write, false for read
 *
 * return non-null for success, null for failed
 * */
void* get_mmap(const char *filename, size_t length, bool is_write = false);

/* delete mmap
 * info: output info when error happens
 * p: memory wil be delete
 * length: memory length
 *
 * */
void delete_mmap(const char *info, void *p, size_t length);

#endif
