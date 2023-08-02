
#ifndef __UTILS_MALLOC_H__
#define __UTILS_MALLOC_H__

#include "types.h"

void *memcpy_malloc(void *dest, void *src, size_t len);
void *memset_malloc(void *s, int c,  unsigned int len);

#endif
