import serial

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

#f = open("../../router_firmware_winbond.bin","rb")
f = open("a.txt","rb")
a = f.read()

b = 0x3000
b = p.writememram(b,a)
print(hex(b))


#limit = b + len(a)
#while(b<limit): 
#    print(hex(p.read32(b)))
#    b+=4
