#include "utils.h"
#include "regdef.h"
#include "uart.h"
#include "cache.h"
#include "uart_debug.h"

extern void* trampoline_irq;
extern void* trampoline_exception;
extern void* exception_dispatcher;
u32 exception_handlers[32];
void (*irq_handlers[32])();

void exception_handler(struct reg_struct *reg_context) {
	u32 status, cause, epc, badaddr;
	mfc0(status, C0_STATUS, 0);
	mfc0(cause, C0_CAUSE, 0);
	mfc0(epc, C0_EPC, 0);
	mfc0(badaddr, C0_BADVADDR, 0);
	//while (1) {
	uart_printf("excepcion\n\r");
	uart_printf("pc es 0x%x \n\r", reg_context->reg31);
	uart_printf("sp es 0x%x \n\r", reg_context->reg29);
	uart_printf("status es 0x%x \n\r", status);
	uart_printf("cause es 0x%x \n\r", cause);
	uart_printf("epc es 0x%x \n\r", epc);
	uart_printf("badaddr es 0x%x \n\r", badaddr);
	//}
	jump((void *)uart_debug_process);
}

void irq_handler(u32 irqn) {
	irq_handlers[irqn]();
}

void set_except_vector(u32 n, void *addr) {
	u32 handler = (u32) addr;
	exception_handlers[n] = handler;
}

void config_exceptions() {
	u32 cause;
	u32 status;
	u32 intctl;
	mtc0(0x80000000, C0_EBASE, 1);		
	mfc0(cause, C0_CAUSE, 0);		
	mtc0((cause & 0xff7fffff), C0_CAUSE, 0); 
	mfc0(intctl, C0_INTCTL, 0);		
	mtc0((intctl & 0xfffffc1f), C0_INTCTL, 1); //intctl

	mfc0(status, C0_STATUS, 0);		//status
	mtc0(status & ~0x400000, C0_STATUS, 0x0);

	memcpy((u32 *)0x80000180, &trampoline_exception, 64);

	for(u32 i = 1;i < 32;i++){
		set_except_vector(i, &exception_dispatcher);
	}
	flush_icache_range(0x80000180, 0x200);
}


void intPrioritySet(u32 source, u32 level) {
	u32 IPRn, IPLn;
	u32 word;
    
	IPRn = level/4;
	IPLn = level%4;
	word = read32((u32 *)(0xbfb40010+IPRn*4));
	word |= source << ((3-IPLn)*8);
	write32((u32 *)(0xbfb40010+IPRn*4), word);
}

void set_irq_priority() {
	u32 IntPriority[32]= {
		0x9,	0x7,	0x16,	0x15,	0x1e,
		0x1d,	0x11,	0x13,	0xa,    0x1,
		0xb,	0xc,	0xd,	0xe,    0x12,	
		0xf,	0x10,	0x8,	0x14,   0x4,
		0x1f,	0x6,	0x5,	0x17,   0x18,
		0x19,   0x1a,	0x1b,	0x1c,	0x3,
		0x2,    0x0
	};

	for (u32 i = 0; i < 32; i++) {
		intPrioritySet(i, IntPriority[i]);
	}
}

void irq_setup() {
	u32 status;
	mfc0(status, C0_STATUS, 0);
	mtc0(((status & ~0xff00)), C0_STATUS, 0)
	set_except_vector(0, &trampoline_irq);
	mfc0(status, C0_STATUS, 0);
	mtc0(((status & ~0xff00) | (0xff00 & 0xff00)), C0_STATUS, 0)
	mfc0(status, C0_STATUS, 0);
	mtc0(((status & ~0x10000001) | (0x10000001 & 0x10000001)), C0_STATUS, 0)
}

void init_irq() {
	set_irq_priority();
	irq_setup();
}

