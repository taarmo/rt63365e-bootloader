/**
 * @name MIPS registers
 * @brief Numbered in the order in which gdb expects to see them.
 * @{
 */


struct gdb_regs {

	/*
	 * saved main processor registers
	 */
	long	 reg0,  reg1,  reg2,  reg3,  reg4,  reg5,  reg6,  reg7;   //zero-a3
	long	 reg8,  reg9,  reg10, reg11, reg12, reg13, reg14, reg15;  //t0-t7
	long	 reg16, reg17, reg18, reg19, reg20, reg21, reg22, reg23;  //s0-s7 
	long	 reg24, reg25, reg26, reg27, reg28, reg29, reg30, reg31;  //t8-ra 
	long     reg32, reg33, reg34, reg35, reg36, reg37; 		  //cp0_status-pc

									  //cp0_cause <- reg36
	/*
	 * Saved floating point registers
	 */
	long	reg38, reg39, reg40, reg41, reg42, reg43, reg44, reg45;  //f0-f7
	long	reg46, reg47, reg48, reg49, reg50, reg51, reg52, reg53; //f8-f15
	long	reg54, reg55, reg56, reg57, reg58, reg59, reg60, reg61; //f16-f23
	long	reg62, reg63, reg64, reg65, reg66, reg67, reg68, reg69; //f24-f31


	long 	cp1_fsr, cp1_fir;
	long 	reg_fp;

	/*
	 * saved cp0 registers
	 */
	long 	cp0_index;
	long 	cp0_epc;
	long	cp0_random;
	long	cp0_entrylo0;
	long	cp0_entrylo1;
	long	cp0_context;
	long	cp0_pagemask;
	long	cp0_wired;
	long	cp0_reg7;
	long	cp0_reg8;
	long	cp0_reg9;
	long	cp0_entryhi;
	long	cp0_reg11;
	long	cp0_reg12;
	long	cp0_reg13;
	long	cp0_reg14;
	long	cp0_prid;
};


