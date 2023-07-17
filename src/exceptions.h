
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include "types.h"

void exception_handler();
void irq_handler(u32 irqn);
void set_except_vector(u32 n, void *addr); 
void config_exceptions();
void intPrioritySet();
void set_irq_priority();
void irq_setup();
void init_irq();

#endif
