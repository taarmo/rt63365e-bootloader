import os, sys, struct
import time

def hexdump(s,sep=" "):
	return sep.join(map(lambda x: "%02x"%ord(x),s))

class UartInterface:
    def __init__(self,device,debug):
        self.dev = device
        self.debug = debug
    def read_full(self,size):
        d = self.dev.read(size)
        return d

    def reply(self,size):
        reply = self.read_full(size)
        #reply = struct.unpack("<
        #if self.debug:
        return reply

    def request(self,opcode,*args):
        if len(args) > 2:
            raise ValueError("Too many arguments")
        args = list(args) + [0] * (2-len(args))
        req = struct.pack(">III",opcode,*args)
        self.dev.write(req)

        #retval = self.reply(4)
        retval = struct.unpack(">I",self.reply(4))[0]
        return retval

class ProxyUart:
    __P_WRITE32 = 0x100
    __P_WRITE8 = 0x101
    __P_READ32 = 0x102
    __P_READ8 = 0x103
    __P_TIMER_COUNT = 0x104
    __P_TIMER_CMP = 0x105
    __P_XXD = 0x106
    

    def __init__(self,iface,debug=False):
        self.iface = iface
        self.debug = debug

    def write32(self,addr,data):
        self.iface.request(self.__P_WRITE32,addr,data)
    def write16(self,addr,data):
        self.iface.request(self.__P_WRITE16,addr,data)
    def write8(self,addr,data):
        self.iface.request(self.__P_WRITE8,addr,data)
    def read32(self,addr):
        return self.iface.request(self.__P_READ32, addr)
    def read16(self,addr):
        return self.iface.request(self.__P_READ16, addr)
    def read8(self,addr):
        return self.iface.request(self.__P_READ8, addr)
    def timer_count(self):
        return self.iface.request(self.__P_TIMER_COUNT)
    def timer_compare(self):
        return self.iface.request(self.__P_TIMER_CMP)
    def xxd(self,addr):
        return self.iface.request(self.__P_XXD, addr)

