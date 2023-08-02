import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

#pv = p.malloc(1000)
#print(hex(pv))

f = open("./doom1.wad.lzma","rb")
data = f.read()
input_size = len(data)
output_size = 4196020
b = p.play_doom(input_size, output_size, data)
print(hex(b))
