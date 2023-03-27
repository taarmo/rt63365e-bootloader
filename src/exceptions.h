
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

void config_exceptions();
void irq_handler();
void exception_handler();
void set_except_vector(int n, void *addr); 

#endif
