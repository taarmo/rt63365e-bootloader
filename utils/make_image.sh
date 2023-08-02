rm 30100.lzma
cp aux_files/30100 .
python3 comp.py
dd if=./aux_files/filesystem_linux of=../main.out.bin bs=1 seek=1313747 count=4648240 conv=notrunc 


#64MB
truncate ../main.out.bin --size=16M
sudo flashrom -p ft2232_spi:type=4232H,port=A -c MX25L12805D -w ../main.out.bin
