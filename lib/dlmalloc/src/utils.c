#include "types.h"
#include "utils.h"

void * memcpy_malloc(void *dest, void *src, size_t len) {
	char *d = dest;
	const char *s = src;
	while (len--)
		*d++ = *s++;
	return dest;
}

void *memset_malloc(void *s, int c, u32 len) {
	unsigned char* p=s;
	while(len--) {
		*p++ = (unsigned char)c;
	}
	return s;
}

