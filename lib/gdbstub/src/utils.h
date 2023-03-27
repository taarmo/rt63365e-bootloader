
int gdb_read_byte(void *address, unsigned char *dest);
int gdb_write_byte(void *addr, unsigned char *dest);

int gdb_write_word(void *addr, unsigned int val);
int gdb_read_word(void *addr, unsigned int val);


unsigned int gdb_read8(unsigned int *addr); 
void gdb_write8(unsigned int *addr, unsigned char val);
unsigned char getDebugChar();
void putDebugChar(unsigned char ch);

#define NULL 0
char* gdb_strcpy(char* destination, const char* source);
int gdb_strncmp(char *s1, char *s2, unsigned int  n); 
void gdb_memcpy32(void *dst, void *src, unsigned int size);
void *gdb_memset(void *s, int c,  unsigned int len); 
