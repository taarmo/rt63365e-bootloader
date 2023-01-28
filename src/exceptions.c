#include "utils.h"
#include "regdef.h"
#include "m32c0.h"
#include "uart.h"
#include "regs.h"

extern void* _sirq;
extern void trampoline_irq;

void exception_handler(struct reg_struct *reg_context){
	u32 status,cause,epc,badaddr;
	mfc0(status,$12,0);
	mfc0(cause,$13,0);
	mfc0(epc,$14,0);
	mfc0(badaddr,$8,0);
	while(1){
		uart_printf("excepcion\n\r");
		uart_printf("pc es 0x%x \n\r",reg_context->pc);
		uart_printf("status es 0x%x \n\r",status);
		uart_printf("cause es 0x%x \n\r",cause);
		uart_printf("epc es 0x%x \n\r",epc);
		uart_printf("badaddr es 0x%x \n\r",badaddr);
	}
	reset();
}

void irq_dispatcher(struct reg_struct *reg_context){
	u32 status,cause,epc,badaddr;
	mfc0(status,$12,0);
	mfc0(cause,$13,0);
	mfc0(epc,$14,0);
	mfc0(badaddr,$8,0);
	uart_printf("interrupcion\n\r");
	uart_printf("pc es 0x%x \n\r",reg_context->pc);
	uart_printf("status es 0x%x \n\r",status);
	uart_printf("cause es 0x%x \n\r",cause);
	uart_printf("epc es 0x%x \n\r",epc);
	uart_printf("badaddr es 0x%x \n\r",badaddr);
	reset();
	return;
}

u32 exception_handlers[32];

void set_except_vector(int n, void *addr)
{
	u32 handler = (u32) addr;
	exception_handlers[n] = handler;
}


void config_exceptions(){
	u32 cause;
	u32 status;
	mtc0(0x80000000,$15,1); //ebase
	mfc0(cause,$13,0);		//cause
	mtc0(cause & (~(1<<18)),$13,0); //cause
	mtc0(cause & 0xfffffc1f,$12,1); //intctl

	mfc0(status,$12,0);		//status
	mtc0(status& ~0x400000,$12,0x0);

	memcpy32((u32 *)0x80000180,&_sirq,248);

	set_except_vector(0,(void *)0x80020200);

	for(int i=1;i<32;i++){
		set_except_vector(i,exception_handler);
	}
	memcpy32((u32 *)0x80000000,irq_dispatcher,0x100);
	memcpy32((u32 *)0x80020000,exception_handlers,31*4);
	memcpy32((u32 *)0x80020200,&trampoline_irq,0x200);

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

