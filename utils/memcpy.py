import serial

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

f = open("../main.out.bin","rb")
size = f.read()
f.close()

addr = 0x0
ret = p.writememram(addr, size)
print(hex(ret))


