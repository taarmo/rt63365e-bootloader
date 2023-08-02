import lzma

#f = open("doom1.wad","rb")
#data = f.read()
#f.close()
#with lzma.open("doom1.wad.lzma", "w") as fl:
#    fl.write(data)

f = open("./30100","rb")
data = f.read()
f.close()
with lzma.open("30100.lzma", "w") as fl:
    fl.write(data)
