from unicorn import *
from keystone import *

import argparse
import os

def auto_int(x):
    return int(x,0)

parser = argparse.ArgumentParser(description="Just an example", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("-s", dest='inject_shellcode',help="inject shellcode mode")
parser.add_argument("-m", type=auto_int, nargs=3, dest='move',help="src_val1<-offset_init src_val2<-offset_fin val3<-dest")
parser.add_argument("-f", type=auto_int, dest='flash',help="flash")
parser.add_argument("-c", type=auto_int, nargs=2 ,dest='clean',help="clean")

args = parser.parse_args()

global dest 

MIPS_CODE = """nop
                    """

def assembly(MIPS_CODE):
    print("Assembling mips code")
    ks = Ks(KS_ARCH_MIPS,KS_MODE_MIPS32+KS_MODE_BIG_ENDIAN)
    MIPS_BYTECODE , _ = ks.asm(MIPS_CODE)
    MIPS_BYTECODE = bytes(MIPS_BYTECODE)
    lenght = len(MIPS_BYTECODE)
    return MIPS_BYTECODE,lenght

def inject_shellcode():
    global MIPS_CODE
    global dest
    dest  = bytearray(open("/home/tarmo/Desktop/routercito_fiu_fiu/bak/backup","rb").read())
    MIPS_BYTECODE,lenght = assembly(MIPS_CODE)
    list_offset = [0x84]
    for i in list_offset:
        dest = dest[:i] + bytes(MIPS_BYTECODE) + dest[i+lenght:]

def move():
    global dest
    source  = bytearray(open("/home/tarmo/Desktop/routercito_fiu_fiu/main.out.bin","rb").read())
    dest  = bytearray(open("/home/tarmo/Desktop/prueba.bin","rb").read())
    source = source[args.move[0]:args.move[1]] 
    lenght = args.move[1] - args.move[0]
    dest = dest[:args.move[2]] + source + dest[args.move[2]+lenght:]

def clean():
    MIPS_CODE = """nop
    """
    global dest
    dest  = bytearray(open("/home/tarmo/Desktop/funciona_sin_purria.bin","rb").read())
    lenght = (args.clean[1]-args.clean[0])//4
    MIPS_CODE = MIPS_CODE*lenght
    MIPS_BYTECODE,l = assembly(MIPS_CODE)
    dest = dest[:args.clean[0]] + bytes(MIPS_BYTECODE) + dest[args.clean[0]+l:]


if args.inject_shellcode:
    inject_shellcode()
    open("prueba.bin","wb").write(dest)
if args.move:
    move()
    open("prueba.bin","wb").write(dest)
if args.clean:
    clean()
    open("prueba.bin","wb").write(dest)
if args.flash:
    os.system("./lzma_app 21D8.bin")
    print("Comprimido\n")
    os.system("dd if=21D8.bin.lzma of=router_firmware_winbond.bin bs=1 seek=8664 conv=notrunc")
    print("Imagen creada\n")


