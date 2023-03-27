
extern unsigned int exception_handlers[32];

void gdb_set_except_vector(int n, void *addr) {
	unsigned int handler = (unsigned int) addr;
	exception_handlers[n] = handler;
}

