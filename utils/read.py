import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

addr = 0x80002000 + 0x100000
#addr = 0x81800000 + 0x1108f0

i = addr 
limit = 0x100
while i < addr+limit:
    print(str(hex(p.read32(i))))
    i+=4
