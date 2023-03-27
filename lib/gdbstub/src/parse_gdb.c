#include "parse_gdb.h"
#include "utils.h"
#define BUFMAX 1500

const char hexchars[] = "0123456789abcdef";
/*
 * Convert a hex character to an int.
 */
static int hex (char ch) {
	if ((ch >= 'a') && (ch <= 'f'))
		return (ch - 'a' + 10);
	if ((ch >= '0') && (ch <= '9'))
		return (ch - '0');
	if ((ch >= 'A') && (ch <= 'F'))
		return (ch - 'A' + 10);
	return (-1);
}

/*
 * Convert length bytes of data starting at addr into hex, placing the
 * result in buf.  Return a pointer to the last (null) char in buf.
 */
char *mem2hex (void *_addr, int length, unsigned char *buf) {
	unsigned int addr = (unsigned int) _addr;

	if (((addr & 0x7) == 0) && ((length & 0x7) == 0)) {      /* dword aligned */
		long long *source = (long long *) (addr);
		long long *limit  = (long long *) (addr + length);

		while (source < limit) {
			int i;
			long long k = *source++;

			for (i = 15; i >= 0; i--)
				*buf++ = hexchars [(k >> (i*4)) & 0xf];
		}
	}
	else if (((addr & 0x3) == 0) && ((length & 0x3) == 0)) { /* word aligned */
		int *source = (int *) (addr);
		int *limit  = (int *) (addr + length);

		while (source < limit) {
			int i;
			int k = *source++;

			for (i = 7; i >= 0; i--)
				*buf++ = hexchars [(k >> (i*4)) & 0xf];
		}
	}
	else if (((addr & 0x1) == 0) && ((length & 0x1) == 0)) { /* halfword aligned */
	
		short *source = (short *) (addr);
		short *limit  = (short *) (addr + length);

		while (source < limit) {
			int i;
			short k = *source++;

			for (i = 3; i >= 0; i--)
				*buf++ = hexchars [(k >> (i*4)) & 0xf];
		}
	}
	else {                                                  /* byte aligned */
		unsigned char *source = (unsigned char *) (addr);
		unsigned char *limit  = (unsigned char *) (addr + length);

		while (source < limit) {
			int i;
			char k = *source++;

			for (i = 1; i >= 0; i--)
				*buf++ = hexchars [(k >> (i*4)) & 0xf];
			}
	}
	*buf = '\0';
	return (buf);
}

/*
 * Convert the hex array buf into binary, placing the result at the
 * specified address.  If the conversion fails at any point (i.e.,
 * if fewer bytes are written than indicated by the size parameter)
 * then return 0;  otherwise return 1.
 */
char *hex2mem(char *buf, char *mem, int count, int binary, int may_fault) {
	int i;
	unsigned char ch;

	for (i=0; i<count; i++)
	{
		if (binary) {
			ch = *buf++;
			if (ch == 0x7d)
				ch = 0x20 ^ *buf++;
		}
		else {
			ch = hex(*buf++) << 4;
			ch |= hex(*buf++);
		}
		if ((*mem++ )!= 0)
			return 0;
	}

	return mem;
}


/*
 * Convert a string from hex to int until a non-hex digit
 * is found.  Return the number of characters processed.
 */
int hexToInt (char **ptr, int *intValue) {
	int numChars = 0;
	int hexValue;

	*intValue = 0;

	while (**ptr) {
		hexValue = hex (**ptr);
		if (hexValue >= 0) {
			*intValue = (*intValue << 4) | hexValue;
			numChars++;
		}
		else
			break;
		(*ptr)++;
	}
	return (numChars);
}

/*
 * Convert a string from hex to long long until a non-hex
 * digit is found.  Return the number of characters processed.
 */
int hexToLongLong (char **ptr, long long *intValue) {
	int numChars = 0;
	int hexValue;

	*intValue = 0;

	while (**ptr)
	{
		hexValue = hex (**ptr);
		if (hexValue >= 0) {
			*intValue = (*intValue << 4) | hexValue;
			numChars++;
		} else
			break;
		(*ptr)++;
	}

	return (numChars);
}

int hexToLong(char **ptr, long *longValue) {
	int numChars = 0;
	int hexValue;

	*longValue = 0;

	while (**ptr) {
		hexValue = hex(**ptr);
		if (hexValue < 0)
			break;

		*longValue = (*longValue << 4) | hexValue;
		numChars ++;

		(*ptr)++;
	}

	return numChars;
}

/*
 * Scan the input stream for a sequence for the form $<data>#<checksum>.
 */
void getpacket (char *buffer) {
	unsigned char checksum;
	unsigned char xmitcsum;
	int i;
	int count;
	char ch;
	do{
		/* wait around for the start character, ignore all other characters */
		while ((ch = getDebugChar ()) != '$');
		checksum = 0;
		xmitcsum = -1;

		count = 0;

		/* now, read until a # or end of buffer is found */
		while ( (count < BUFMAX-1) && ((ch = getDebugChar ()) != '#') )
		  checksum += (buffer[count++] = ch);

		/* make sure that the buffer is null-terminated */
		buffer[count] = '\0';

		if (ch == '#') {
			xmitcsum = hex (getDebugChar ()) << 4;
			xmitcsum += hex (getDebugChar ());
			if (checksum != xmitcsum)
				putDebugChar ('-'); /* failed checksum */
			else {
				putDebugChar ('+');       /* successful transfer */
				/* if a sequence char is present, reply the sequence ID */
				if (buffer[2] == ':') {
					putDebugChar (buffer[0]);
					putDebugChar (buffer[1]);
					  /* remove sequence chars from buffer */
					for (i = 3; i <= count; i++)
						buffer[i - 3] = buffer[i];
				}
			}
		}
	} while (checksum != xmitcsum);
}

/*
 * Get a positive/negative acknowledgment for a transmitted packet.
 */
char getAck (void) {
	char c;
	do{
		c = getDebugChar ();
	}while ((c != '+') && (c != '-'));
	return c;
}

/*
 * Send the packet in buffer and wait for a positive acknowledgement.
 */
void putpacket (char *buffer) {
	int checksum;

	/* $<packet info>#<checksum> */
	do {
		char *src = buffer;
		putDebugChar ('$');
		checksum = 0;

		while (*src != '\0') {
			int runlen = 0;

			/* Do run length encoding */
			while ((src[runlen] == src[0]) && (runlen < 99))
				runlen++;
			if (runlen > 3) {
				int encode;
				/* Got a useful amount */
				putDebugChar (*src);
				checksum += *src;
				putDebugChar ('*');
				checksum += '*';
				checksum += (encode = (runlen - 4) + ' ');
				putDebugChar (encode);
				src += runlen;
			} else {
				putDebugChar (*src);
				checksum += *src;
				src++;
			}
		}

		putDebugChar ('#');
		putDebugChar (highhex (checksum));
		putDebugChar (lowhex (checksum));
	} while  (getAck () != '+');
}

