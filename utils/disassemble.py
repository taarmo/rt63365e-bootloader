from unicorn import *
from capstone import *
from keystone import *

import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)


def assembly(MIPS_CODE):
    md = Cs(CS_ARCH_MIPS,CS_MODE_MIPS32+CS_MODE_BIG_ENDIAN)
    for instruction in md.disasm(MIPS_CODE,0x1000):
        print("0x%x:\t%s\t%s" % (instruction.address, instruction.mnemonic, instruction.op_str))

#print(hex(p.read32(0xbfc01000)))
i = 0x80000000 
limit = i+1000
l = b""

while(i < limit):
    c = p.read32(i)
    ch = c.to_bytes(4,'big')
    l += ch 
    print(str(hex(i)) + ": " + str(hex(c)))
    i +=4

print("-------------------------------")
assembly(l)
#i=0
#init_28 = 822476853
#
#print(init_28)
#while i < 0x100:
#    p.write32(0xbfbc0000,0x02000115)      #lanzar rafaga
#    p.write32(0xbfbc0004,0xff050102) 
#    #p.write32(0xbfbc0008,0xff01ffff) 
#    #p.write32(0xbfbc000c,0xff01ffff) 
#    #p.write32(0xbfbc0010,0xff01ffff) 
#    #p.write32(0xbfbc0014,0xff01ffff) 
#    #print(hex(p.read32(0xbfbc0000)))
#    i+=4



