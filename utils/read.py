import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB1', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

print("58: " + str(hex(p.read32(0xbfb00058))))
print("64: " + str(hex(p.read32(0xbfb00064))))
print("8c: " + str(hex(p.read32(0xbfb0008c))))


#while(i < limit):
#    c = p.read32(i)
#    p.write32(i,0xffffffff)
#    ch = c.to_bytes(4,'big')
#    l += ch 
#    print(str(hex(i)) + ": " + str(hex(c)))
#    i +=4


