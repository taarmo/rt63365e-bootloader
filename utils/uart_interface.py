import os, sys, struct
import time

class UartInterface:
    
    def __init__(self, device, debug):
        self.dev = device
        self.debug = debug

    def read_full(self, size):
        d = self.dev.read(size)
        return d

    def reply(self, size):
        reply = self.read_full(size)
        return reply

    def cmd(self, cmd):
        self.dev.write(cmd)
    
    def write_data(self, data):
        self.dev.write(data)

    def proxyreq(self, req):
        self.cmd(req)
        retval = struct.unpack(">I",self.reply(4))[0] 
        return retval


class ProxyUart:
    __P_WRITE32 = 0x100
    __P_WRITE8 = 0x101
    __P_READ32 = 0x102
    __P_READ8 = 0x103
    __P_TIMER_COUNT = 0x104
    __P_JUMP = 0x105
    __P_LOAD_ELF = 0x106
    __P_LOAD_KERNEL = 0x107
    __P_WRITE_MEM_RAM= 0x108
    __P_WRITE_MEM_FLASH= 0x109
    __P_LCD= 0x10a
    __P_MALLOC= 0x10b
    __P_DOOM= 0x10c
    

    def __init__(self, iface, debug=False):
        self.iface = iface
        self.debug = debug

    def request(self, opcode, *args):
        if len(args) > 4:
            raise ValueError("Too many arguments")
        args = list(args) + [0] * (4-len(args))
        req = struct.pack(">IIIII", opcode, *args)
        reply = self.iface.proxyreq(req)
        return reply

    def writemem(self, op, data, *args):
        if len(args) > 4:
            raise ValueError("Too many arguments")
        args = list(args) + [0] * (4-len(args))
        req = struct.pack(">IIIII", op, *args)
        self.iface.cmd(req)
        self.iface.write_data(data)
        retval = struct.unpack(">I",self.iface.reply(4))[0] 
        return retval

    def write32(self, addr, data):
        self.request(self.__P_WRITE32, addr, data)
    def write16(self, addr, data):
        self.request(self.__P_WRITE16, addr, data)
    def write8(self, addr, data):
        self.request(self.__P_WRITE8, addr, data)
    def read32(self, addr):
        return self.request(self.__P_READ32, addr)
    def read16(self, addr):
        return self.request(self.__P_READ16, addr)
    def read8(self, addr):
        return self.request(self.__P_READ8, addr)
    def timer_count(self):
        return self.request(self.__P_TIMER_COUNT)
    def jump(self, addr):
        return self.request(self.__P_JUMP, addr)
    def load_elf(self, input_addr, input_size, data):
        return self.writemem(self.__P_LOAD_ELF, data, input_addr, input_size)
    def load_kernel(self, input_addr, output_addr, input_size, output_size, data):
        return self.writemem(self.__P_LOAD_KERNEL, data, input_addr, output_addr, input_size, output_size)
    def writememram(self, input_addr, input_size, data):
        return self.writemem(self.__P_WRITE_MEM_RAM, data, input_addr, input_size)
    def writememflash(self, input_addr, input_size, data):
        return self.writemem(self.__P_WRITE_MEM_FLASH, data, input_addr, input_size)
    def lcd(self):
        return self.request(self.__P_LCD)
    def malloc(self, size):
        return self.request(self.__P_MALLOC, size)
    def play_doom(self, input_size, output_size, data):
        return self.writemem(self.__P_DOOM, data, input_size, output_size)


