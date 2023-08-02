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

addr = 0x80000000 
limit = addr+1000
l = b""

while(addr < limit):
    c = p.read32(addr)
    ch = c.to_bytes(4,'big')
    l += ch 
    print(str(hex(addr)) + ": " + str(hex(c)))
    addr +=4

print("-------------------------------")
assembly(l)



