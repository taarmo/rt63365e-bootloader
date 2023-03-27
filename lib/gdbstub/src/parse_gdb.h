

char *mem2hex (void *_addr, int length, unsigned char *buf); 
char *hex2mem(char *buf, char *mem, int count, int binary, int may_fault); 
int hexToInt (char **ptr, int *intValue);
int hexToLongLong (char **ptr, long long *intValue); 
int hexToLong(char **ptr, long *longValue); 
void getpacket (char *buffer); 
char getAck (void);
void putpacket (char *buffer); 

#define highhex(x) hexchars [(x >> 4) & 0xf]
#define lowhex(x) hexchars [x & 0xf]
