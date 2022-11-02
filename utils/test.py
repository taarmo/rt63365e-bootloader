import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

#p.write32(0xbfb00834, 0x0)
#p.write32(0xbfb00080, 0x20)
#p.write32(0xbfb00080, 0x0)
#

i=0
init_28 = 822476853

print(init_28)
while i < 0x100:
    p.write32(0xbfbc0000,0x02000115)      #lanzar rafaga
    p.write32(0xbfbc0004,0xff050102) 
    #p.write32(0xbfbc0008,0xff01ffff) 
    #p.write32(0xbfbc000c,0xff01ffff) 
    #p.write32(0xbfbc0010,0xff01ffff) 
    #p.write32(0xbfbc0014,0xff01ffff) 
    #print(hex(p.read32(0xbfbc0000)))
    i+=4

#0xbfbc0000
#p.write32(0xbfbc0000, (0x0a000102)) 
#1er tamaño de rafaga en bytes de envio
#2o tamaño de rafaga en bytes de recepcion 
#3er nibble enable
#7o  nibble datos
#8o  nibble datos

#0xbfbc0004
#p.write32(0xbfbc0004,0xfff6ff00) 
#AÑADE DATOS
#1er 2o nibble opcode
#7o 8o nibble datos
#5o 6o nibble datos



