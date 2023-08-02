import serial
import time
import sys
import os

#exec !! sx yourbinary.bin

#En tftp>
#mode binary
#put bootloader.bin
#quit

init = True

def cut_bootloader():
    with open("../main.out.bin", "rb") as fr:
        fw = open("bootloader.bin", "wb")
        data = fr.read()
        size = len(data)
        for i in reversed(data):
            if (i):
                break;
            size-=1
        if (size % 0x10):
            size = size + (0x10 - (size % 0x10))
        fw.write(data[0:size])
        fw.close()
        return size

def printf(string):
    sys.stdout.write(string)
    sys.stdout.flush()

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
size = cut_bootloader()
size_bootloader = str(size).encode('ascii')

print("Waiting for a prompt...")
ser.flush()
while True:
    if(ser.read(1) == b'b' and ser.read(1) == b'l' and ser.read(1) == b'd' and ser.read(1) == b'r' and ser.read(1) == b'>' and init):
        time.sleep(0.5)
        ser.write(b"ipaddr 192.168.1.5")
        ser.write(b"\r")
        time.sleep(0.5)
        printf("Ip cambiada\n")
        os.system(b"tftp 192.168.1.5")
        init = False
    ser.write(b"\r")
    while(init == False):
        if(ser.read(1) == b'T' and ser.read(1) == b'o' and ser.read(1) == b't' and ser.read(1) == b'a' and ser.read(1) == b'l'):
            ser.write(b"\r")
            ser.write(b"flash 0 80020000 "+ size_bootloader)
            ser.write(b"\r")
            os.system(b"screen /dev/ttyUSB0 115200")
            exit()



