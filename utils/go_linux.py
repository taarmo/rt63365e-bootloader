import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

f = open("./30100.lzma","rb")
data = f.read()

input_addr = 0x81800000
output_addr = 0x80002000
input_size = len(data)
output_size = 3291456
b = p.load_kernel(input_addr, output_addr, input_size, output_size, data)
print(hex(b))
f.close()
