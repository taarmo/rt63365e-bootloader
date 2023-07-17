import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)


led1 = 0xbfb00080
led2 = 0xbfb00834 #coleccion de leds

GPIO_BASE = 0xbfbf0200
CTRL = GPIO_BASE+0x0
DATA = GPIO_BASE+0x4
DRAIN = GPIO_BASE+0x14
UNK = GPIO_BASE+0x20

#p.write32(led1,0x0)
#p.write32(led2,0x1000000)
#p.write32(led2,0x0)
#p.write32(CTRL,0x10000)
#p.write32(DATA,0x13)

def config_gpio(pin):
    p.write32(CTRL, 1 << ((pin & 0xf) << 1) | p.read32(CTRL));
    p.write32(DRAIN, 1 << (pin & 0x1f)  | p.read32(DRAIN));

def gpiooff(pin):
    p.write32(DATA, 1 << (pin & 0x1f) | p.read32(DATA))
    time.sleep(0.5)
    
def gpioon(pin):
    p.write32(DATA, ~(1 << (pin & 0x1f)) & p.read32(DATA))
    time.sleep(0.5)


# 4 es el fucking numero de la bestia yeah!
config_gpio(4)
gpiooff(4)

print("CTRL " + str(hex(p.read32(CTRL))))
print("DATA " + str(hex(p.read32(DATA))))
print("drain " + str(hex(p.read32(GPIO_BASE+0x14))))

