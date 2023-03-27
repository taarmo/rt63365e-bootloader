
unsigned int gdb_read8(unsigned int *addr) {
	unsigned char val;
	__asm__ volatile("lb\t%0,%1" : "=r"(val): "m"(*addr));
	return val;
}

void gdb_write8(unsigned int *addr, unsigned char val) {
	__asm__ volatile("sb\t%1,%0" : "+m"(*addr):"r"(val));
}


unsigned char getDebugChar(){
	while(!((gdb_read8((unsigned int *)0xbfbf0017)) & 0x1));
	return gdb_read8((unsigned int *)0xbfbf0003);
}

void putDebugChar(unsigned char ch){
	while(!((gdb_read8((unsigned int *)0xbfbf0017)) & 0x20));
	gdb_write8((unsigned int *)0xbfbf0003,ch);
}


char* gdb_strcpy(char* destination, const char* source)
{
    if (destination == '\x00') {
        return 0x0;
    }

    char *ptr = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return ptr;
}

int gdb_strncmp(char *s1, char *s2, unsigned int  n) {

	if (n == 0)
		return (0);
	do {
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return (0);
}

void *gdb_memset(void *s, int c,  unsigned int len) {
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

