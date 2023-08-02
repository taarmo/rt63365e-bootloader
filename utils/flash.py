
import serial

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

f = open("../main.out.bin","rb")
data = f.read()
print(data)

addr = 0
input_size = len(data)
b = p.writememflash(addr, input_size, data)
print(hex(b))
f.close()

