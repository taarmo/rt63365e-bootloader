#include "utils.h"

void config_uart(){
	write32(0xbfbf0003,1);
	write32(0xbfbf0007,0);
	write32(0xbfbf000b,0xf);
	write32(0xbfbf000f,3);
	write32(0xbfbf0013,0);
	write32(0xbfbf0027,0);
	write32(0xbfbf002c,0xea00fde8);
}
