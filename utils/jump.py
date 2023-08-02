import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

addr = 0x80002000
p.jump(addr)
while 1:
    print(uartinterface.read_full(1).decode('utf-8'), end ="")

