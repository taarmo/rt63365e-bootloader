#include "utils.h"
#include "m32c0.h"
#include "uart.h"
#include "frame_registers.h"

extern u32 _irq_size;
extern void* trampoline_irq;
extern void* trampoline_exception;
extern void* exception_dispatcher;
u32 exception_handlers[32];

void exception_handler(struct reg_struct *reg_context) {
	u32 status,cause,epc,badaddr;
	mfc0(status,$12,0);
	mfc0(cause,$13,0);
	mfc0(epc,$14,0);
	mfc0(badaddr,$8,0);
	uart_printf("excepcion\n\r");
	uart_printf("pc es 0x%x \n\r",reg_context->reg31);
	uart_printf("status es 0x%x \n\r",status);
	uart_printf("cause es 0x%x \n\r",cause);
	uart_printf("epc es 0x%x \n\r",epc);
	uart_printf("badaddr es 0x%x \n\r",badaddr);
	while(1);
	//reset();
}

void irq_handler(struct reg_struct *reg_context) {
	u32 status,cause,epc,badaddr;
	mfc0(status,$12,0);
	mfc0(cause,$13,0);
	mfc0(epc,$14,0);
	mfc0(badaddr,$8,0);
	uart_printf("interrupcion\n\r");
	uart_printf("pc es 0x%x \n\r",reg_context->reg31);
	uart_printf("status es 0x%x \n\r",status);
	uart_printf("cause es 0x%x \n\r",cause);
	uart_printf("epc es 0x%x \n\r",epc);
	uart_printf("badaddr es 0x%x \n\r",badaddr);
	return;
}


void set_except_vector(int n, void *addr) {
	u32 handler = (u32) addr;
	exception_handlers[n] = handler;
}


void config_exceptions() {
	u32 cause;
	u32 status;
	mtc0(0x80000000,$15,1); //ebase
	mfc0(cause,$13,0);		//cause
	mtc0(cause & (~(1<<18)),$13,0); //cause
	mtc0(cause & 0xfffffc1f,$12,1); //intctl

	mfc0(status,$12,0);		//status
	mtc0(status& ~0x400000,$12,0x0);

	memcpy32((u32 *)0x80000180,&trampoline_exception, 64);
	memcpy32((u32 *)0x80000200,&trampoline_irq, 64);

	//set_except_vector(0,(void *)0x80020200);

	for(int i=1;i<32;i++){
		set_except_vector(i,&exception_dispatcher);
	}

	memcpy32((u32 *)0x80000000, exception_handlers, 32*4);

	//config cache
	//u32 a = (0x80000000+0x180) & 0xffffffe0; 		//-0x20
	//u32 a = (0x80000000+0x180); 
	u32 a = 0x80000000; 
	//u32 b = (0x80000000+0x200- 1U) & 0xffffffe0;  //-0x20
	//u32 b = (0x80000000+0x200);
	u32 b = (0x80030000+0x200);
	cache(a,0x15);
	sync();
	cache(a,0x10);
	while(a != b){
		a += 0x20;
		cache(a,0x15);
		sync();
		cache(a,0x10);
	}	
}

