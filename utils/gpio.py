import serial
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

class State:
    ON = 0 
    OFF = 1 

state = State()

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
#p.write32(CTRL,0x10100)
def control_dcx(state):
    p.write32(led1, state << 5)  

def config_gpio(pin):
    p.write32(CTRL, 1 << ((pin & 0xf) << 1) | p.read32(CTRL));
    p.write32(DRAIN, 1 << (pin & 0x1f)  | p.read32(DRAIN));

def gpiooff(pin):
    p.write32(DATA, 1 << (pin & 0x1f) | p.read32(DATA))
    
def gpioon(pin):
    p.write32(DATA, ~(1 << (pin & 0x1f)) & p.read32(DATA))


#config_gpio(4)

#while 1:
#    p.write32(led2,0x1000000)
#    p.write32(led2,0x0)
#
#pin = state.ON
#control_dcx(pin)
#pin ^=1

print("CTRL " + str(hex(p.read32(CTRL))))
print("DATA " + str(hex(p.read32(DATA))))
print("drain " + str(hex(p.read32(GPIO_BASE+0x14))))

