import serial
import struct
import time

from uart_interface import *
usbuart = serial.Serial('/dev/ttyUSB0', 115200)
uartinterface = UartInterface(usbuart,False)
p = ProxyUart(uartinterface,False)

def solve():
    if (((p.read32(0xbfb00064) & 0xffff0000) != 0x30000) and ((p.read32(0xbfb00064) & 0xffff0000) != 0x40000)):
        return 8 << (((p.read32(0xbfb20074) << 0xb) >> 0x1d) - 1);

    if ((p.read32(0xbfb0008c) << 6) < 0):
        return 8 << (((p.read32(0xbfb20044) << 0xb) >> 0x1d)) - 1;

    uVar1 = (p.read32(0xbfb20004) << 0xe) >> 0x1e
    iVar3 = ((p.read32(0xbfb20004) << 10) >> 0x1e) + 8
    iva2 = 2
    print("ivar3: " + str(iVar3))
    if ((uVar1 != 0) or (iVar3 != 8)):
        iVar2 = 4;
    return(((1 << (uVar1 + 0xb) << iVar3) * 2 * iVar2) >> 0x14)

size = solve()
print(str((size/1024)/1024) + "MB")
