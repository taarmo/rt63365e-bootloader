import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)
import time

data = 0xbfbf0204
ctrl = 0xbfbf0200
odrain = 0xbfbf0214
random = 0xbfbf0220

def read_all():
    print(str(hex(odrain)) + ": " + str(hex(p.read32(odrain))))
    print(str(hex(random)) + ": " + str(hex(p.read32(random))))
    print(str(hex(data)) + ": " + str(hex(p.read32(data))))
    print(str(hex(ctrl)) + ": " + str(hex(p.read32(ctrl))))


#p.write32(0xbfb00834, 0x1000000)
#p.write32(0xbfb00834, 0x0)
#p.write32(0xbfb00080, 0x20)
#p.write32(0xbfb00080, 0x0)
print(hex(p.timer_count()))
time.sleep(1)
print(hex(p.timer_count()))


#print(hex(p.read32(0xbfc00000)))

#i = 1
#while i < (i<<31):
#    p.write32(ctrl,i)
#    i = i<<1
#    print(str(hex(data)) + ": " + str(hex(p.read32(data))))

