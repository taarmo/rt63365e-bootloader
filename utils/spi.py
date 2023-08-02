import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

SPI_CTL_BUSY = 0x00010000
SPI_ENABLE = 0x00000100
SPI_CTL_TX_RX_CNT_MASK = 0x000000ff

class State:
    ON = 1
    OFF = 0 

state = State()

#NOP = 0x0
#WRR = 0x1
#PAGE_PGRM = 0x2
#READ = 0x3
#WR_DISABLE = 0x4
#RDSR = 0x5
#WREN = 0x6
#ERASE = 0x7
#
#stm_opcodes = [[NOP,0,0],[WRR,2,0],[PAGE_PGRM,4,0],[READ,8,4],[WR_DISABLE,1,0],[RDSR,1,1],[WREN,1,0],[0x20,4,0]]

def spi_write_addr_data(op, to, data, size):
    n_bytes_data = size-1 
    remaindering = n_bytes_data % 4

    reg_value = 0x0
    reg = p.read32(0xbfbc0000)

    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

    reg_value = p.read32(0xbfbc0028)
    p.write32(0xbfbc0028,reg_value | (1 << 2))
    p.write32(0xbfbc002c,0x28000000|(n_bytes_data<<3))

    i = 4
    while(i < ((n_bytes_data>>2)<<2) ):
        p.write32(0xbfbc0008+i, data[i+3] << 16 | data[i+2]<<8 | data[i+1] | data[i+4]<<24)
        i+=4

    if(remaindering == 1):
        p.write32(0xbfbc0008+i, data[i+1] )

    elif(remaindering == 2):
        p.write32(0xbfbc0008+i, data[i+2]<<8 | data[i+1] )

    elif(remaindering == 3):
        p.write32(0xbfbc0008+i, data[i+3] << 16 | data[i+2]<<8 | data[i+1] )


    p.write32(0xbfbc0004, (to&0x00ffffff)<<8 | data[0])
                                                                    #opcode
    reg = (reg & ~SPI_CTL_TX_RX_CNT_MASK) | n_bytes_data | SPI_ENABLE | (op << 24)

    p.write32(0xbfbc0000, reg)

    ##clean
    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

    p.write32(0xbfbc002c,0x00000000);
    p.write32(0xbfbc0028,reg_value);

def spi_write_data(data, rx, size):

    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

    if (size >= 1 and size <= 4):
        d = data[0]
        if (size == 2):
            d |= data[1] << 24
        elif (size == 3):
            d |= data[1] << 24 | data[2] << 16
        elif (size == 4):
            d |= data[1] << 24 | data[2] << 16 | data[3] << 8

        p.write32(0xbfbc0004, d)

        reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | rx<<4 | size | SPI_ENABLE;
        p.write32(0xbfbc0000, reg)


    elif (size >= 5):
        n_bytes_data = size-5 
        remaindering = (n_bytes_data % 4) 

        reg_value = p.read32(0xbfbc0028)
        p.write32(0xbfbc0028, reg_value | (1 << 2))
        p.write32(0xbfbc002c, 0x28000000 | (n_bytes_data << 3))

        i = 4 
        while(i < (((size-1)  >> 2) << 2) ):
            p.write32(0xbfbc0008+(i-4), data[i+2] << 16 | data[i+1] << 8 | data[i] | data[i+3] << 24)
            i+=4

        if(remaindering == 1):
            p.write32(0xbfbc0008+(i-4), data[i+1] )

        elif(remaindering == 2):
            p.write32(0xbfbc0008+(i-4), data[i+2]<<8 | data[i+1] )

        elif(remaindering == 3):
            p.write32(0xbfbc0008+(i-4), data[i+3] << 16 | data[i+2]<<8 | data[i+1] )

        d = (data[1] << 24 | data[2] << 16 | data[3] << 8) | data[4] 
        p.write32(0xbfbc0004, d)
        reg = ((reg & ~SPI_CTL_TX_RX_CNT_MASK) | n_bytes_data | rx << 4 |SPI_ENABLE | data[0] << 24)

        p.write32(0xbfbc0000, reg)

        p.write32(0xbfbc002c,0x00000000);
        p.write32(0xbfbc0028,reg_value);

    #if(rx > 0):
    #    rem = rx % 4
    #    while reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY:
    #        pass
    #    while i < rx:
    #        reg = p.read32(0xbfbc0008 + i) 
    #        i+=4
    #        rx-=4
    #    reg &= (0xffffffff >> ((rem) << 3));
    #else:
    #    reg = 0


    #return reg  

def control_dcx(state):
    p.write32(0xbfb00080, state << 5)  

def send_cmd(op):
    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

    p.write32(0xbfbc0004, op)

    reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | 1 | SPI_ENABLE;

    p.write32(0xbfbc0000,reg)



def send_cmd_addr(op,addr,data):
    val = 0
    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)
                           # byte 3    #byte 2                  #byte 1               #byte 0            
    p.write32(0xbfbc0008, (data)>>24| (data & 0x00ff0000)>>8 |(data&0x0000ff00)<<8 | (data & 0xff)<<24) 

    p.write32(0xbfbc0004, (addr&0x00ffffff) << 8 | stm_opcodes[op][0] & 0xff)

    reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | stm_opcodes[op][2]<<4 | stm_opcodes[op][1] | SPI_ENABLE;

    p.write32(0xbfbc0000,reg)
    if(stm_opcodes[op][2] > 0):
        while reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY:
            pass
        reg = p.read32(0xbfbc0008) 
        reg &= (0xffffffff >> ((4 - stm_opcodes[op][2]) << 3));
    else:
        reg = 0
    return reg  

#def erase_one_block(addr):
#    finished = False
#    opcode = stm_opcodes[ERASE][0]
#    temp = ((addr << 8) | (opcode))  
#    send_cmd(WREN,0x0,0x0) 
#    while(reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY):
#        pass
#    p.write32(0xbfbc0004,temp)
#    reg = addr & 0xff000000| (reg & ~SPI_CTL_TX_RX_CNT_MASK) | stm_opcodes[ERASE][1]+1 | SPI_ENABLE
#    p.write32(0xbfbc0000,reg)
#
#    while(not finished):
#        reg = create_frame(RDSR,0x0,0x0);
#        if (not(reg & 0x1)): 
#            finished = TRUE
#



