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
        return reply

    #def cmd(self,cmd,payload):
    def cmd(self,cmd):
        #if len(payload) > 28:
        #    raise ValueError("Incorrect payload size %d"%len(payload))

        #payload = payload + "/x00"*(28 - len(payload))
        #command = struct.pack("<I",cmd) + payload
        self.dev.write(cmd)
        #print(cmd)

    def proxyreq(self,req):
        self.cmd(req)
        retval = struct.unpack(">I",self.reply(4))[0] 
        return retval

    def writemem(self,op,addr,data):
        size = len(data)
        req = struct.pack(">IIII", op ,addr, size,0x0)

        self.dev.write(req)
        self.dev.write(data)
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
    __P_WRITE_MEM_RAM= 0x107
    __P_WRITE_MEM_FLASH= 0x108
    

    def __init__(self,iface,debug=False):
        self.iface = iface
        self.debug = debug

    def request(self,opcode,*args):
        if len(args) > 3:
            raise ValueError("Too many arguments")
        args = list(args) + [0] * (3-len(args))
        req = struct.pack(">IIII",opcode,*args)
        reply = self.iface.proxyreq(req)
        return reply

    def write32(self,addr,data):
        self.request(self.__P_WRITE32,addr, data)
    def write16(self,addr,data):
        self.request(self.__P_WRITE16,addr, data)
    def write8(self,addr,data):
        self.request(self.__P_WRITE8,addr, data)
    def read32(self,addr):
        return self.request(self.__P_READ32, addr)
    def read16(self,addr):
        return self.request(self.__P_READ16, addr)
    def read8(self,addr):
        return self.request(self.__P_READ8, addr)
    def timer_count(self):
        return self.request(self.__P_TIMER_COUNT)
    def timer_compare(self):
        return self.request(self.__P_TIMER_CMP)
    def xxd(self,addr):
        return self.request(self.__P_XXD, addr)
    def writememram(self,addr,data):
        return self.iface.writemem(self.__P_WRITE_MEM_RAM,addr, data)
    def writememflash(self,addr):
        return self.request(self.__P_WRITE_MEM_FLASH, addr)


