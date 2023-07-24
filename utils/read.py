import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

#p.writememflash(0x3000)
i = 0
while i < 0x100:
    print(str(hex(p.read32(0xbfc03000 + i))))
    i+=4


#while(i < limit):
#    c = p.read32(i)
#    p.write32(i,0xffffffff)
#    ch = c.to_bytes(4,'big')
#    l += ch 
#    print(str(hex(i)) + ": " + str(hex(c)))
#    i +=4


