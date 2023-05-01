
int gdb_read_byte(void *address, unsigned char *dest);
int gdb_write_byte(void *addr, unsigned char *dest);

int gdb_write_word(void *addr, unsigned int val);
int gdb_read_word(void *addr, unsigned int val);


unsigned int gdb_read8(unsigned int *addr); 
void gdb_write8(unsigned int *addr, unsigned char val);
unsigned char getDebugChar();
void putDebugChar(unsigned char ch);

char* gdb_strcpy(char* destination, const char* source);
int gdb_strncmp(char *s1, char *s2, unsigned int  n); 
void gdb_memcpy32(void *dst, void *src, unsigned int size);
void *gdb_memset(void *s, int c,  unsigned int len); 

#define jump(addr)			 \
	__asm__ volatile("j\t " #addr);

#define mfc0(source, reg, val)							\
	if(val == 0){								\
		__asm__ volatile("mfc0\t%0, " #reg : "=r"(source));		\
	}else{									\
		__asm__ volatile("mfc0\t%0, " #reg "," #val : "=r"(source));	\
	}

#define mtc0(source,reg,val)							\
	if(val == 0){								\
		__asm__ volatile("mtc0\t%0, " #reg :: "r"(source));		\
	}else{									\
		__asm__ volatile("mtc0\t%0, " #reg "," #val :: "r"(source)); 	\
	}

#define cache(base,op)       							\
	__asm__ volatile("cache %1, (%0)":: "r"(base),"i"(op));

#define sync() 									\
	__asm__ volatile("sync 0x0":::);

#define hazardbarrier() 							\
	__asm__ volatile("ssnop\n"					   	\
			 "ssnop\n"					   	\
			 "ssnop\n"					   	\
			 "ehb\n":::);  

