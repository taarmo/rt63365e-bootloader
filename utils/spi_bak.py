import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

SPI_CTL_BUSY = 0x00010000
SPI_ENABLE = 0x00000100
SPI_CTL_TX_RX_CNT_MASK = 0x000000ff

NOP = 0x0
WRR = 0x1
PAGE_PGRM = 0x2
READ = 0x3
WR_DISABLE = 0x4
RDSR = 0x5
WREN = 0x6
ERASE = 0x7 

stm_opcodes = [[NOP,0,0],[WRR,2,0],[PAGE_PGRM,4,0],[READ,8,4],[WR_DISABLE,1,0],[RDSR,1,1],[WREN,1,0],[0x20,4,0]]

def spi_write(to,data,size):
    if(size <= 0):
        return
    n_bytes_data = size-1 
    xact_len = n_bytes_data

    reg_value = 0x0
    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

    reg_value = p.read32(0xbfbc0028)
    p.write32(0xbfbc0028,reg_value | (1 << 2))
    p.write32(0xbfbc002c,0x28000000|(xact_len<<3))

                        #byte 2              byte 1             byte 0
    p.write32(0xbfbc0008,(data>>16)&0xff | (data&0x0000ff00) |(data&0xff)<<16) 

    #p.write32(0xbfbc0008,data) 
    #p.write32(0xbfbc000c,data)
    #p.write32(0xbfbc0010,data)
    #p.write32(0xbfbc0014,data)
    #p.write32(0xbfbc0018,data)
    #p.write32(0xbfbc001c,data)
    #p.write32(0xbfbc0020,data)
    #p.write32(0xbfbc0024,data)

                                               # byte 3
    p.write32(0xbfbc0004, (to&0x00ffffff)<<8 | (data>>24) & 0xff)
                                                                    #opcode
    reg = (reg & ~SPI_CTL_TX_RX_CNT_MASK) | xact_len | SPI_ENABLE | (0x02 << 24)
    p.write32(0xbfbc0000, reg)
    #p.write32(0xbfbc0038,0x1)

def send_cmd(op,addr,data,size):
    val = 0
    i = 0
    reg = p.read32(0xbfbc0000)
    while (reg & SPI_CTL_BUSY) == True:
        reg = p.read32(0xbfbc0000)

                               # byte 3    #byte 2                  #byte 1               #byte 0            
    while (i<size):
        p.write32(0xbfbc0008+i, data[3+i] | data[2+i] << 8 | data[1+i] << 16 | data[0+i]<<24) 
        i+=4

    p.write32(0xbfbc0004, (addr&0x00ffffff) << 8 | stm_opcodes[op][0] & 0xff)

    reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | stm_opcodes[op][2]<<4 | stm_opcodes[op][1]+size | SPI_ENABLE;

    p.write32(0xbfbc0000,reg)
    #if(stm_opcodes[op][2] > 0):
    #    while reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY:
    #        pass
    #    reg = p.read32(0xbfbc0008) 
    #    reg &= (0xffffffff >> ((4 - stm_opcodes[op][2]) << 3));
    #else:
    #    reg = 0
    return reg  

#def send_cmd(op,addr,data):
#    val = 0
#    reg = p.read32(0xbfbc0000)
#    while (reg & SPI_CTL_BUSY) == True:
#        reg = p.read32(0xbfbc0000)
#
#                           # byte 3    #byte 2                  #byte 1               #byte 0            
#    p.write32(0xbfbc0008, (data)>>24| (data & 0x00ff0000)>>8 |(data&0x0000ff00)<<8 | (data & 0xff)<<24) 
#
#    p.write32(0xbfbc0004, (addr&0x00ffffff) << 8 | stm_opcodes[op][0] & 0xff)
#
#    reg = reg & ~SPI_CTL_TX_RX_CNT_MASK | stm_opcodes[op][2]<<4 | stm_opcodes[op][1] | SPI_ENABLE;
#
#    p.write32(0xbfbc0000,reg)
#    #if(stm_opcodes[op][2] > 0):
#    #    while reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY:
#    #        pass
#    #    reg = p.read32(0xbfbc0008) 
#    #    reg &= (0xffffffff >> ((4 - stm_opcodes[op][2]) << 3));
#    #else:
#    #    reg = 0
#    return reg  

def erase_one_block(addr):
    finished = False
    opcode = stm_opcodes[ERASE][0]
    temp = ((addr << 8) | (opcode))  
    send_cmd(WREN,0x0,0x0,0x0) 
    while(reg := p.read32(0xbfbc0000) & SPI_CTL_BUSY):
        pass
    p.write32(0xbfbc0004,temp)
    reg = addr & 0xff000000| (reg & ~SPI_CTL_TX_RX_CNT_MASK) | stm_opcodes[ERASE][1]+1 | SPI_ENABLE
    p.write32(0xbfbc0000,reg)

    #while(not finished):
    #    reg = create_frame(RDSR,0x0,0x0);
    #    if (not(reg & 0x1)): 
    #        finished = TRUE


#CONTENIDO 0xbfbc0028 --> 0x68880

#p.write32(0xbfbc0028,0x68880)# yep
#p.write32(0xbfbc002c,0x0)# yep
#
#print(hex(send_cmd(RDSR,0x0))) #spi_write(0x0,0xabcdef12)
#erase_one_block(0x0)
#print(hex(send_cmd(READ,0x0)))

#buf = [0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23]
buf = [0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27]


#send_cmd(WREN,0x0,buf,0x0)
send_cmd(PAGE_PGRM,0x3000,buf,len(buf))
#erase_one_block(0x0)


#i=0xbfc00000
#limit = i+0x100
#while(i < limit):
#    print(str(hex(i)) + ": " + str(hex(p.read32(i))))
#    i+=4
#

