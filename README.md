
# rt63365e-bootloader


### Requirements
```
sudo apt install gcc-mips-linux-gnu
sudo apt install tftp
```
Optional

```
sudo apt install binwalk
sudo apt install flashrom
```
### Compile
```
make
```
> [!WARNING]
> if you use Asus DSL-N14U choosing the wrong make command will brick your device
> `make RAM64=1`


### Installing the bootloader

```
cd utils
python3 flash_factory_loader_hg532s.py
```

Connnect the ethernet wire port 1, power on the router

Tftp commands
```
mode binary
put bootloader.bin
quit
```

Wait the Bienvenido and Reset the router

### Changing the bootloader

In utils/flash.py, change "main.out.bin"
```
f = open("../main.out.bin","rb")
#DONT CHANGE ADDR IN THE SCRIPT!!!
```
and

```
cd utils
python3 flash.py   
```

### Achivements

![1694008759971](https://github.com/t4rmop/rt63365e-bootloader/assets/98432158/849e7d5a-52ce-4f09-a1a8-0882c7e8de1e)

https://github.com/t4rmop/rt63365e-bootloader/assets/98432158/180529c3-f82d-4ca9-9938-b21551240662



