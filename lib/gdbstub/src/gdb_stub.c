#include "../../../src/uart.h"
#include "gdb_exceptions.h"
#include "utils.h"
#include "frame_registers.h"
#include "regdef.h""
#include "parse_gdb.h"
#include "mips_opcode.h"
#include "inst.h"

#define BUFMAX 1500

extern void *gdb_exception_dispatcher;

typedef unsigned int mips_register_t;
static mips_register_t *registers;
extern unsigned int exception_handlers[32];
extern char hexchars[];

static unsigned char inBuffer[BUFMAX];
static unsigned char outBuffer[BUFMAX];
//static unsigned char gdbstub_flush_caches;


struct z0break
{
  /* List support */
  struct z0break *next;
  struct z0break *prev;

  unsigned char *address;
  unsigned instr;
};

#define BREAKNUM 32
static struct z0break z0break_arr[BREAKNUM];
static struct z0break *z0break_avail = NULL;
static struct z0break *z0break_list  = NULL;

struct gdb_regs *regs_ret = NULL;

/*
 * clear a software breakpoint
 */
void set_breakpoint(struct gdb_regs *regs, char* addr, int len) {
	struct z0break *z0;

	//if (type != 0) {
	//	/* We support only software break points so far */
	//	strcpy(outBuffer, "E02");
	//	return;
	//}

	if (len != R_SZ) {     /* was 1 */
		gdb_strcpy(outBuffer, "E03");
		return;
	}

	/* Let us check whether this break point already set */
	for (z0=z0break_list; z0!=NULL; z0=z0->next) {
		if (z0->address == addr) {
			break;
		}
	}

	if (z0 != NULL) {
		/* we already have a breakpoint for this address */
		gdb_strcpy(outBuffer, "E04");
		return;
	}

	/* Let us allocate new break point */
	if (z0break_avail == NULL) {
		gdb_strcpy(outBuffer, "E05");
		return;
	}

	/* Get entry */
	z0 = z0break_avail;
	z0break_avail = z0break_avail->next;

	/* Fill it */
	z0->address = addr;

	if( z0->address == (unsigned char *) regs->cp0_epc ) {
		/* re-asserting the breakpoint that put us in here, so
		we'll add the breakpoint but leave the code in place
		since we'll be returning to it when the user continues */
		z0->instr = 0xffffffff;
	}
	else {
		/* grab the instruction */
		z0->instr = *(z0->address);
		/* and insert the break */
		*(z0->address) = BREAK_INSTR;
	}

	/* Add to the list */
	struct z0break *znxt = z0break_list;

	z0->prev = NULL;
	z0->next = znxt;

	if( znxt ) znxt->prev = z0;
		z0break_list = z0;
		gdb_strcpy(outBuffer, "OK");
         return;
}

void clear_breakpoint(struct gdb_regs *regs, char* addr, int len) {
	struct z0break *z0;


	//if (type != 0) {
	//	/* We support only software break points so far */
	//	return;
	//}

	if (len != R_SZ) {
		gdb_strcpy(outBuffer, "E02");
		return;
	}

/* Let us check whether this break point set */
	for (z0=z0break_list; z0!=NULL; z0=z0->next) {
		if (z0->address == addr) {
			break;
		}
	}

	if (z0 == NULL) {
		/* Unknown breakpoint */
		gdb_strcpy(outBuffer, "E03");
		return;
	}


	if( z0->instr != 0xffffffff )
	{
		/* put the old instruction back  */
		*(z0->address) = z0->instr;
	}

	/* Unlink entry */
	struct z0break *zprv = z0->prev, *znxt = z0->next;

	if( zprv ) zprv->next = znxt;
	if( znxt ) znxt->prev = zprv;

	if( !zprv ) z0break_list = znxt;

	znxt = z0break_avail;

	z0break_avail = z0;
	z0->prev = NULL;
	z0->next = znxt;

	gdb_strcpy(outBuffer, "OK");
}


static int computeSignal (void) {
	int exceptionCode = (registers[CAUSE] & CAUSE_EXCMASK) >> CAUSE_EXCSHIFT;

	switch (exceptionCode)
	{
		case EXC_INT:
		/* External interrupt */
			return SIGINT;

		case EXC_RI:
		/* Reserved instruction */
		case EXC_CPU:
		/* Coprocessor unusable */
			return SIGILL;

		case EXC_BP:
			/* Break point */
			return SIGTRAP;

		case EXC_OVF:
			/* Arithmetic overflow */
		case EXC_TRAP:
			/* Trap exception */
		case EXC_FPE:
			/* Floating Point Exception */
			return SIGFPE;

		case EXC_IBE:
			/* Bus error (Ifetch) */
		case EXC_DBE:
			/* Bus error (data load or store) */
			return SIGBUS;

		case EXC_MOD:
			/* TLB modification exception */
		case EXC_TLBL:
			/* TLB miss (Load or Ifetch) */
		case EXC_TLBS:
			/* TLB miss (Store) */
		case EXC_ADEL:
			/* Address error (Load or Ifetch) */
		case EXC_ADES:
			/* Address error (Store) */
			return SIGSEGV;

		case EXC_SYS:
			/* System call */
			return SIGSYS;

		default:
			return SIGTERM;
	}
}



void show_gdbregs(struct gdb_regs * regs) {

	uart_printf("zero: %08lx at: %08lx\n\r",
	       regs->reg0, regs->reg1);
	uart_printf("v0: %08lx v1: %08lx a0: %08lx a1: %08lx a2: %08lx a3: %08lx t0: %08lx t1: %08lx\n\r",
	       regs->reg2, regs->reg3, regs->reg4, regs->reg5,
	       regs->reg6, regs->reg7, regs->reg8, regs->reg9);
	uart_printf("t2: %08lx t3: %08lx t4: %08lx t5: %08lx t6: %08lx t7: %08lx s0: %08lx s1: %08lx\n\r",
	       regs->reg10, regs->reg11, regs->reg12, regs->reg13,
	       regs->reg14, regs->reg15, regs->reg16, regs->reg17);
	uart_printf("s2: %08lx s3: %08lx s4: %08lx s5: %08lx s6: %08lx s7: %08lx t8: %08lx t9: %08lx\n\r",
	       regs->reg18, regs->reg19, regs->reg20, regs->reg21,
	       regs->reg22, regs->reg23, regs->reg24, regs->reg25);
	uart_printf("k0: %08lx k1: %08lx gp: %08lx sp: %08lx fp: %08lx ra: %08lx\n\r\n",
	       regs->reg26, regs->reg27, regs->reg28, regs->reg29, regs->reg30, regs->reg31);
	uart_printf("cp0_index: %08lx cp0_status: %08lx cp0_cause: %08lx cp0_epc: %08lx\n\r\n",
	       regs->cp0_index, regs->reg32, regs->reg36, regs->cp0_epc);
	/*
	 * Saved cp0 registers
	 */
	//uart_printf("epc  : %08lx\nStatus: %08lx\nCause : %08lx\n",
	//       regs->cp0_epc, regs->cp0_status, regs->cp0_cause);
}


static void gdb_stub_report_exception_info(struct gdb_regs *regs,unsigned char *ptr) {
	unsigned long *stack;
	int sigval;


	/* Send trap type (converted to signal)  */
	stack = (long *)regs->reg29;			/* stack ptr */
	sigval = computeSignal();

	/*
	 * reply to host that an exception has occurred
	 */
	ptr = outBuffer;


	*ptr++ = 'T';
	*ptr++ = hexchars[sigval >> 4];
	*ptr++ = hexchars[sigval & 0xf];

	/*
	 * Send Error PC
	 */
	*ptr++ = hexchars[REG_EPC >> 4];
	*ptr++ = hexchars[REG_EPC & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((char *)&regs->cp0_epc, sizeof(long), ptr);
	*ptr++ = ';';

	/*
	 * Send frame pointer
	 */
	*ptr++ = hexchars[FP >> 4];
	*ptr++ = hexchars[FP & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((char *)&regs->reg_fp, sizeof(long), ptr);
	*ptr++ = ';';

	/*
	 * Send stack pointer
	 */
	*ptr++ = hexchars[SP >> 4];
	*ptr++ = hexchars[SP & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((char *)&regs->reg29, sizeof(long), ptr);
	*ptr++ = ';';

	*ptr++ = 0;
}


void gdb_handle_exception (struct gdb_regs *regs) {
	unsigned char flag = 1;
	int host_has_detached = 0;
	long addr,regno,length;
	unsigned char *ptr;
	long long regval;
	int sigval;
	int loop;

	//show_gdbregs(regs);
	registers = (mips_register_t *)regs;
	sigval = computeSignal();

	//if( sigval == 9 && regs->cp0_epc == (unsigned long)breakinst ) {
	//	//gdbstub_printf( DEBUG_SINGLESTEP, "skipping breakinst\n" );
	//	regs->cp0_epc += 4;
	//}
	if(flag) { 
		*((unsigned int *)regs->reg37) = 0x0;
		flag = 0;
	}

	gdb_stub_report_exception_info(regs,ptr); 
	putpacket (outBuffer);

	while (!(host_has_detached)) {
		outBuffer[0] = '\0';
		getpacket (inBuffer);
		switch (inBuffer[0]) {
			case '?':
				outBuffer[0] = 'S';
				outBuffer[1] = hexchars[sigval >> 4];
				outBuffer[2] = hexchars[sigval & 0xf];
				outBuffer[3] = 0;
				break;
			case 'q':
				if (gdb_strncmp((char*)&inBuffer[1], "Supported", 9)==0) {
					gdb_strcpy(outBuffer,"swbreak+;");
					putpacket(outBuffer);
					gdb_strcpy (outBuffer, "OK");
				}
				break;

			case 'v':
				if ( gdb_strncmp((char*)&inBuffer[1], "Cont", 4)==0) {
					if( inBuffer[5] == '?' ){
						//gdb_strcpy(outBuffer, "vCont;c;C;s;S");
						gdb_strcpy(outBuffer, "c;C;s;S");
					}else if( inBuffer[6] == 'c' ){
						ptr = &inBuffer[1];
						if (hexToInt(&ptr, &addr))
							regs->cp0_epc = addr;
						goto ret;
					}else{
						goto ret;
					}
				}
				break;

			case 'D':
			/* remote system is detaching - return OK and exit from debugger */
				gdb_strcpy (outBuffer, "OK");
				host_has_detached = 1;
				break;

			case 'd': /* toggle debug flag */
				/* can print ill-formed commands in valid packets & checksum errors */
				break;


			case 'g':
				ptr = outBuffer;
				ptr = mem2hex((char *)&regs->reg0,         32*sizeof(long), ptr); /* r0...r31 */
				ptr = mem2hex((char *)&regs->reg32,   6*sizeof(long), ptr); /* cp0 */
				ptr = mem2hex((char *)&regs->reg38,           32*sizeof(long), ptr); /* f0...31 */
				ptr = mem2hex((char *)&regs->cp1_fsr,    2*sizeof(long),  ptr); /* cp1 */
				ptr = mem2hex((char *)&regs->reg_fp,         2*sizeof(long),  ptr) ; /* frp */
				ptr = mem2hex((char *)&regs->cp0_index,  16*sizeof(long), ptr); /* cp0 */
				break;
			case 'G':
				ptr = &inBuffer[1];
				hex2mem(ptr, (char *)regs, 90*4, 0, 0);
				gdb_strcpy(outBuffer, "OK");
			case 'P':
				/* Pn...=r...  Write register n... with value r... - return OK */
				ptr = &inBuffer[1];
				if (hexToInt(&ptr, &regno) && *ptr++ == '=' &&	hexToLongLong(&ptr, &regval)) {
					registers[regno] = regval;
					gdb_strcpy (outBuffer, "OK");
				} else 
				       gdb_strcpy (outBuffer, "E00"); /* E00 = bad "set register" command */
				break;
			case 'm':
				ptr = &inBuffer[1];
				if (hexToLong(&ptr, &addr) && *ptr++ == ',' && hexToInt(&ptr, &length)) {
					if (mem2hex((char *)addr, length, outBuffer))
						break;
					gdb_strcpy(outBuffer, "E03");
				} else {
					gdb_strcpy(outBuffer, "E01");
				}
				break;
			case 'M':
				ptr = &inBuffer[1];

				if (hexToLong(&ptr, &addr) && *ptr++ == ',' && hexToInt(&ptr, &length)	&& *ptr++ == ':') {
					if (hex2mem(ptr, (char *)addr, length, 0, 1))
						gdb_strcpy(outBuffer, "OK");
					else
						gdb_strcpy(outBuffer, "E03");
				}
				else
					gdb_strcpy(outBuffer, "E02");
				break;
			case 'Z':
				ptr = &inBuffer[1];

				if (!hexToInt(&ptr, &loop) || *ptr++ != ',' ||
				    !hexToInt(&ptr, &addr) || *ptr++ != ',' ||
				    !hexToInt(&ptr, &length)
				    ) {
					gdb_strcpy(outBuffer, "E01");
					break;
				}

				set_breakpoint(regs,addr,length);

				break;

				/*
				 * Clear breakpoint
				 */
			case 'z':
				ptr = &inBuffer[1];

				if (!hexToInt(&ptr, &loop) || *ptr++ != ',' ||
				    !hexToInt(&ptr, &addr) || *ptr++ != ',' ||
				    !hexToInt(&ptr, &length)
				    ) {
					gdb_strcpy(outBuffer, "E01");
					break;
				}

				///* only support software breakpoints */
				//gdb_strcpy(outBuffer, "E03");
				//if (loop != 0 ||
				//    length < 1 ||
				//    length > 4 ||
				//    (unsigned long) addr < 4096)
				//	break;

				clear_breakpoint(regs, addr, length);

				break;

			}
		putpacket(outBuffer);
	}
	ret:
	regs_ret = regs;
	return;

}

void mips_gdb_stub_install() {

	struct z0break *z0;

	gdb_set_except_vector(9, &gdb_exception_dispatcher);
	gdb_memcpy32((unsigned int *)0x80000000,exception_handlers,31*4);
	gdb_memset(outBuffer, 0x0, 1500*sizeof(unsigned char));
	gdb_memset(inBuffer, 0x0, 1500*sizeof(unsigned char));

	z0break_avail = NULL;
	z0break_list  = NULL;

	/* z0breaks list init, now we'll do it so it makes sense... */
	for (int i=0; i<BREAKNUM; i++) {
		gdb_memset( (z0= &z0break_arr[i]), 0, sizeof(struct z0break));
	
		z0->next = z0break_avail;
		z0break_avail = z0;
	}

   /* mips_break(1);  disabled so user code can choose to invoke it or not */
}


