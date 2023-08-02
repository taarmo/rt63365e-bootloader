from spi import *


ILI9341_PWCTR1 = 0xC0
ILI9341_PWCTR2 = 0xC1
ILI9341_VMCTR1 = 0xC5
ILI9341_VMCTR2 = 0xC7
ILI9341_MADCTL = 0x36
ILI9341_PIXFMT = 0x3A
ILI9341_FRMCTR1 = 0xB1
ILI9341_DFUNCTR = 0xB6
ILI9341_GAMMASET = 0x26
ILI9341_GMCTRP1 = 0xE0
ILI9341_GMCTRN1 = 0xE1
ILI9488_CASET =  0x2A
ILI9488_PASET =  0x2B
ILI9488_RAMWR =  0x2C

init_commands = [[0xEF, 0x03, 0x80, 0x02], 
[0xCF, 0x00, 0XC1, 0X30],
[0xED, 0x64, 0x03, 0X12, 0X81],
[0xE8, 0x85, 0x00, 0x78],
[0xCB, 0x39, 0x2C, 0x00, 0x34, 0x02],
[0xF7, 0x20],
[0xEA, 0x00, 0x00],
[ILI9341_PWCTR1, 0x23], #Power control
[ILI9341_PWCTR2, 0x10], # Power control
[ILI9341_VMCTR1, 0x3e, 0x28], # VCM control
[ILI9341_VMCTR2, 0x86], # VCM control2
[ILI9341_MADCTL, 0x48], # Memory Access Control
[ILI9341_PIXFMT, 0x55],
[ILI9341_FRMCTR1, 0x00, 0x18],
[ILI9341_DFUNCTR, 0x08, 0x82, 0x27], #Display Function Control
[0xF2, 0x00], #Gamma Function Disable
[ILI9341_GAMMASET, 0x01], #Gamma curve selected
[ILI9341_GMCTRP1, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00], #Set Gamma
[ILI9341_GMCTRN1, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
	0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F, # Set Gamma
3, 0xb1, 0x00, 0x10, # FrameRate Control 119Hz
0]]


def init(init_commands): 
    for i in init_commands:
        control_dcx(State.OFF)
        send_cmd(i[0])
        control_dcx(State.ON)
        spi_write_data(i[1:],0,len(i[1:]))



def setAddrWindow(x0, y0, x1, y1) :
    control_dcx(State.OFF)
    send_cmd(ILI9488_CASET);  #Column addr set
    control_dcx(State.ON)
    addr_commands.append(x0 >> 8)
    addr_commands.append(x0 & 0xff)
    addr_commands.append(x1 >> 8)
    addr_commands.append(x1 & 0xff)
    spi_write_data(addr_commands, 0, len(addr_commands));     #XEND
    addr_commands.clear()

    control_dcx(State.OFF)
    send_cmd(ILI9488_PASET);  #Row addr set
    control_dcx(State.ON)
    addr_commands.append(y0 >> 8)
    addr_commands.append(y0 & 0xff)
    addr_commands.append(y1 >> 8)
    addr_commands.append(y1 & 0xff)
    spi_write_data(addr_commands, 0, len(addr_commands))

    send_cmd(ILI9488_RAMWR); #write to RAM


def write16BitColor(color) :
    r = (color & 0xF800) >> 11;
    g = (color & 0x07E0) >> 5;
    b = color & 0x001F;

    color = []

    r = (r * 255) // 31;
    g = (g * 255) // 63;
    b = (b * 255) // 31;

    color.append(r)
    color.append(g)
    color.append(b)
    control_dcx(State.OFF)
    spi_write_data(color,0 , len(color));
    control_dcx(State.ON)

def drawPixel(x, y, color) :

    setAddrWindow(x,y,x+1,y+1);

    control_dcx(State.ON)

    write16BitColor(color);

    control_dcx(State.OFF)



p.lcd()

