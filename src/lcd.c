#include "lcd.h"
#include "spi.h"
#include "types.h"
#include "uart.h"
#include "utils.h"
#include "gpio.h"

s16 _width = ILI9341_TFTWIDTH;
s16 _height = ILI9341_TFTHEIGHT;
s16 addr_row = (short) 0xFFFF;
s16 addr_col = (short) 0xFFFF;
s16 old_x1 = (short) 0xffff, old_x2 = (short) 0xffff;
s16 old_y1 = (short) 0xffff, old_y2 = (short) 0xffff;

u8 init_commands[] = {
	0xEF, 3, 0x03, 0x80, 0x02, 
	0xCF, 3, 0x00, 0xC1, 0x30,
	0xED, 4, 0x64, 0x03, 0x12, 0x81,
	0xE8, 3, 0x85, 0x00, 0x78,
	0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
	0xF7, 1, 0x20,
	0xEA, 2, 0x00, 0x00,
	ILI9341_PWCTR1, 1, 0x23, //#Power control
	ILI9341_PWCTR2, 1, 0x10, //# Power control
	ILI9341_VMCTR1, 2, 0x3e, 0x28, //# VCM control 
	ILI9341_VMCTR2, 1, 0x86, //# VCM control2
	ILI9341_MADCTL, 1, 0x48, //# Memory Access Control
	ILI9341_PIXFMT, 1, 0x55,
	ILI9341_FRMCTR1, 2, 0x00, 0x18, 
	ILI9341_DFUNCTR, 3,  0x08, 0x82, 0x27, //#Display Function Control
	0xF2, 1, 0x00, //#Gamma Function Disable
	ILI9341_GAMMASET, 1, 0x01, //#Gamma curve selected
	ILI9341_GMCTRP1, 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
	0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00, //#Set Gamma
	ILI9341_GMCTRN1, 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 
	0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F, //# Set Gamma
	0xb1, 2, 0x00, 0x10, //# FrameRate Control 119Hz
	ILI9341_SLPOUT, 0,// Exit Sleep
	ILI9341_DISPON, 0 // Display on
};

void init_lcd() {
	char numArgs;
	u8 comm;
	u8 *p = init_commands;
	for (u8 i = 0; i <= size_init; i++) {
		comm = *p;
		writeCommand(*(p++));
		if (comm == ILI9341_DISPON) break;
		numArgs = *(p++);
		while (numArgs-- > 0) {
			//spi_write_data((p+2), 0, numArgs);
			writedata(*(p++));
		} 
	
	}
	delay_us(500000);
}

void setAddrWindow(s16 x1, s16 y1, s16 x2, s16 y2) {
	if (x1 != old_x1 || x2 != old_x2) {
		writeCommand(ILI9341_CASET); // Column address set
		writedata(x1 >> 8);
		writedata(x1 & 0xff);
		writedata(x2 >> 8);
		writedata(x2 & 0xff);
		old_x1 = x1;
		old_x2 = x2;
	}
	if (y1 != old_y1 || y2 != old_y2) {
		writeCommand(ILI9341_PASET); // Row address set
		writedata(y1 >> 8);
		writedata(y1 & 0xff);
		writedata(y2 >> 8);
		writedata(y2 & 0xff);
		old_y1 = y1;
		old_y2 = y2;
	}
	writeCommand(ILI9341_RAMWR); // Write to RAM
}

void drawPixel(s16 x, s16 y, u16 color) {
	setAddrWindow(x, y, x+1, y+1);
	writedata(color >> 8);
	writedata(color & 0xff);
}

void fillScreen(u16 color) {
	fillRect(0, 0, _width, _height, color);
}

u16 color565(u8 r, u8 g, u8 b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void fillRect(s16 x, s16 y, s16 w, s16 h, u16 color) {
	if((x >= _width) || (y >= _height)) return;
	if((x + w - 1) >= _width)  w = _width  - x;
	if((y + h - 1) >= _height) h = _height - y;

	setAddrWindow(x, y, w, h);
	s32 total = 2*w*h;
	while (total-- > 0) { 
		writedata(color);
	}

}

void drawarr(u32 height, u32 width, u16 arr[height][width]) {
	for(int y=0; y < height; y++) {
		for(int x=0; x < width; x++ ) {
			drawPixel(x, y, arr[y][x]);
		}
	}
}

void setRotation(u8 m) {
	u8 rotation = m % 4; // can't be higher than 3
	writeCommand(ILI9341_MADCTL);
	switch (rotation) {
		case 0:
			m = (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR);
			_width = ILI9341_TFTWIDTH;
			_height = ILI9341_TFTHEIGHT;
			break;
		case 1:
			m = (ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
			_width = ILI9341_TFTHEIGHT;
			_height = ILI9341_TFTWIDTH;
			break;
		
		case 2:
			m = (ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
			_width = ILI9341_TFTWIDTH;
			_height = ILI9341_TFTHEIGHT;
			break;
		case 3:
			m = (ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
			_width = ILI9341_TFTHEIGHT;
			_height = ILI9341_TFTWIDTH;
			break;
	}
	writedata(m);
	old_x1 = (short) 0xffff;
	old_x2 = (short) 0xffff;
	old_y1 = (short) 0xffff;
	old_y2 = (short) 0xffff;
}

