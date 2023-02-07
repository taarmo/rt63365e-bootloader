rm logfile
kill $(pidof socat)
socat -v /dev/ttyUSB0,b115200,raw  PTY,link=$HOME/myserial,raw,echo=0 2>logfile &
python3 memcpy.py
sleep 0.1
cat logfile

